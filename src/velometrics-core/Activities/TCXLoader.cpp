
#include "TCXLoader.h"

#include <qfile.h>
#include <QXmlStreamReader>
#include "../Metrics/TelemetryTrack.h"

void TcxLoader::calculateDerivedMetrics(TelemetryTrack& track) {

    if (track.samples.count() < 2){
        return;
    }

    track.samples[0].addValue(TelemetryValueName::Speed,0.0,Unit::KilometerPerHour, TelemetryValueType::Double);
    track.samples[0].addValue(TelemetryValueName::Gradient,0.0,Unit::Percent,TelemetryValueType::Double);

    for (int i = 1; i < track.samples.count(); ++i){
        TelemetrySample* previous  = &track.samples[i -1];
        TelemetrySample* current = &track.samples[i];

        const double previousDistance = previous->values.value(TelemetryValueName::Distance).value.toDouble();
        const double currentDistance = current->values.value(TelemetryValueName::Distance).value.toDouble();

        const double previousAltitude = previous->values.value(TelemetryValueName::Altitude).value.toDouble();
        const double currentAltitude = current->values.value(TelemetryValueName::Altitude).value.toDouble();

        const double deltaDistance = currentDistance - previousDistance;
        const double deltaAltitude = currentAltitude - previousAltitude;

        const double deltaTimeSeconds = previous->timestamp.msecsTo(current->timestamp) / 1000.0;

        //
        // Speed (km/h)
        //
        double speedKmh = 0;
        if (deltaTimeSeconds > 0.0 && deltaDistance > 0.0){
            speedKmh = (deltaDistance / deltaTimeSeconds) * 3.6;
        }

        current->addValue(
            TelemetryValueName::Speed,
            speedKmh,
            Unit::KilometerPerHour,
            TelemetryValueType::Double);


        //
        // Gradient (%)
        //
        double gradient = 0;
        if (std::abs(deltaDistance) > 0.0 && deltaAltitude > 0.0){
            gradient = (deltaAltitude / deltaDistance) * 100.0;
        }

        current->addValue(
            TelemetryValueName::Gradient,
            gradient,
            Unit::Percent,
            TelemetryValueType::Double);

    }
}

bool TcxLoader::load(const QString& filename, TelemetryTrack& track){
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }

    track.clear();
    QXmlStreamReader xml(&file);

    while (!xml.atEnd()){
        xml.readNext();
        if (!xml.isStartElement())
            continue;

        if (xml.name() != QLatin1String("Trackpoint"))
            continue;

        TelemetrySample sample;

        while (!(xml.isEndElement() && xml.name() == QLatin1String("Trackpoint"))){
            xml.readNext();
            if (!xml.isStartElement())
                continue;

            //
            // Time
            //
            if (xml.name() == QLatin1String("Time"))
            {
                sample.timestamp =
                    QDateTime::fromString(
                        xml.readElementText(),
                        Qt::ISODate);
            }
            //
            // Altitude
            //
            else if (xml.name() == QLatin1String("AltitudeMeters"))
            {
                QString value = xml.readElementText();
                sample.addValue(
                    TelemetryValueName::Altitude,
                    value.toDouble(),
                    Unit::Meter,
                    TelemetryValueType::Double);
            }

            //
            // Distance
            //
            else if (xml.name() == QLatin1String("DistanceMeters"))
            {

                sample.addValue(
                    TelemetryValueName::Distance,
                    xml.readElementText().toDouble(),
                    Unit::Meter,
                    TelemetryValueType::Double);
            }

            //
            // Cadence
            //
            else if (xml.name() == QLatin1String("Cadence")){
                sample.addValue(
                    TelemetryValueName::Cadence,
                    xml.readElementText().toInt(),
                    Unit::rpm,
                    TelemetryValueType::Integer);
            }

            //
            // Heart Rate
            //
            else if (xml.name() == QLatin1String("HeartRateBpm")){
                while (!(xml.isEndElement() &&
                         xml.name() == QLatin1String("HeartRateBpm"))){
                    xml.readNext();
                    if (xml.isStartElement() &&
                        xml.name() == QLatin1String("Value")){
                        sample.addValue(
                            TelemetryValueName::HeartRate,
                            xml.readElementText().toInt(),
                            Unit::BPM,
                            TelemetryValueType::Integer);
                    }
                }
            }
            //
            // GPS Position
            //
            else if (xml.name() == QLatin1String("Position")){
                GeoPoint gps;
                while (!(xml.isEndElement() &&
                         xml.name() == QLatin1String("Position"))){
                    xml.readNext();
                    if (!xml.isStartElement())
                        continue;
                    if (xml.name() == QLatin1String("LatitudeDegrees")){
                        gps.latitude = xml.readElementText().toDouble();
                    }
                    else if (xml.name() == QLatin1String("LongitudeDegrees")){
                        gps.longitude = xml.readElementText().toDouble();
                    }
                }
                sample.addValue(TelemetryValueName::GPS,QVariant::fromValue<GeoPoint>(gps),
                    Unit::None,
                    TelemetryValueType::GeoLocation);
            }

            else if (xml.name() == QLatin1String("Speed")){
                QString value = xml.readElementText();
                double speed = value.toDouble();
                speed = speed * 3.6;
                sample.addValue(
                    TelemetryValueName::Speed,
                    speed,
                    Unit::KilometerPerHour,
                    TelemetryValueType::Double);
            }
        }

        track.addSample(sample);
    }
    calculateDerivedMetrics(track);
    return !xml.hasError();
}
