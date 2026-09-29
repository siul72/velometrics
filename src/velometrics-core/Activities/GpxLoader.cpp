#include "GpxLoader.h"

#include <QFile>
#include <QXmlStreamReader>
#include <QDateTime>
#include <QtMath>
#include "../Metrics/TelemetryTrack.h"

namespace
{
    double degreesToRadians(const double degrees)
    {
        return degrees * M_PI / 180.0;
    }

    double haversineDistance(
     const GeoPoint p1,
    const GeoPoint p2)
    {
        constexpr double EarthRadiusMeters = 6371000.0;

        const double dLat = degreesToRadians(p2.latitude - p1.latitude);
        const double dLon = degreesToRadians(p2.longitude - p1.longitude);

        const double a =
            qPow(qSin(dLat / 2.0), 2) +
            qCos(degreesToRadians(p1.latitude)) *
            qCos(degreesToRadians(p2.latitude)) *
            qPow(qSin(dLon / 2.0), 2);

        const double c = 2.0 * qAtan2(qSqrt(a), qSqrt(1.0 - a));

        return EarthRadiusMeters * c;
    }

}

bool GpxLoader::load(const QString& filename, TelemetryTrack& track)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    track.clear();

    QXmlStreamReader xml(&file);

    TelemetrySample sample {};
    bool insideTrackPoint = false;

    while (!xml.atEnd())
    {
        xml.readNext();

        if (xml.isStartElement())
        {
            if (const QStringView name = xml.name(); name == u"trkpt")
            {

                insideTrackPoint = true;
                GeoPoint gps;

                gps.latitude =
                    xml.attributes().value("lat").toDouble();

                gps.longitude =
                    xml.attributes().value("lon").toDouble();

                sample.addValue(TelemetryValueName::GPS,QVariant::fromValue<GeoPoint>(gps),
                   Unit::None,
                   TelemetryValueType::GeoLocation);
            }
            else if (insideTrackPoint && name == u"ele")
            {
                const auto value = xml.readElementText().toDouble();

                sample.addValue(
                    TelemetryValueName::Altitude,
                    value,
                    Unit::Meter,
                    TelemetryValueType::Double);
            }
            else if (insideTrackPoint && name == u"time")
            {
                sample.timestamp =
                    QDateTime::fromString(
                        xml.readElementText(),
                        Qt::ISODate);

                sample.timestamp = sample.timestamp.toUTC();
            }
            else if (insideTrackPoint && name == u"hr")
            {

                sample.addValue(
                            TelemetryValueName::HeartRate,
                            xml.readElementText().toInt(),
                            Unit::BPM,
                            TelemetryValueType::Integer);
            }
        }
        else if (xml.isEndElement())
        {
            if (xml.name() == u"trkpt")
            {
                track.addSample(sample);
                insideTrackPoint = false;
            }
        }
    }

    if (xml.hasError())
    {
        qWarning() << "GPX parse error:" << xml.errorString();
        return false;
    }

    calculateDerivedMetrics(track);

    return true;
}

void GpxLoader::calculateDerivedMetrics(TelemetryTrack& track)
{
    if (track.samples.count() < 2)
        return;

    double totalDistance = 0.0;

    for (int i = 1; i < track.samples.count(); ++i)
    {
        auto* previous = &track.samples[i - 1];
        auto* current = &track.samples[i];

        const double distance =
            haversineDistance(
                 previous->values.value(TelemetryValueName::GPS).value.value<GeoPoint>(),
                 current->values.value(TelemetryValueName::GPS).value.value<GeoPoint>()
                );

        const double timeSeconds =
            static_cast<double> (previous->timestamp.msecsTo(current->timestamp)) / 1000.0;

        totalDistance += distance;
        current->addValue(
            TelemetryValueName::Distance,
            totalDistance,
            Unit::Meter,
            TelemetryValueType::Double);

        auto speedKmh = 0.0;
        if (timeSeconds > 0.0){
            speedKmh = (distance / timeSeconds) * 3.6;
        }

        current->addValue(
           TelemetryValueName::Speed,
           speedKmh,
           Unit::KilometerPerHour,
           TelemetryValueType::Double);

        const double altitudeDelta =
            current->values.value(TelemetryValueName::Altitude).value.toDouble() -
                previous->values.value(TelemetryValueName::Altitude).value.toDouble();

        auto gradient = 0.0;
        if (distance > 0.0){
            gradient =
                (altitudeDelta / distance) * 100.0;
        }

        current->addValue(
          TelemetryValueName::Gradient,
          gradient,
          Unit::Percent,
          TelemetryValueType::Double);
    }
}
