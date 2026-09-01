
#include "TCXLoader.h"

#include <qfile.h>
#include <QXmlStreamReader>
#include "../Metrics/TelemetryTrack.h"


bool TcxLoader::load(const QString& filename, TelemetryTrack& track)
{
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

        while (!(xml.isEndElement() &&
                 xml.name() == QLatin1String("Trackpoint")))
        {
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
                sample.addValue(
                    TelemetryValueName::Altitude,
                    xml.readElementText().toDouble(),
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
            else if (xml.name() == QLatin1String("Cadence"))    
            {
                sample.addValue(
                    TelemetryValueName::Cadence,

                    xml.readElementText().toInt(),
                    Unit::rpm,
                    TelemetryValueType::Integer);
            }

            //
            // Heart Rate
            //
            else if (xml.name() == QLatin1String("HeartRateBpm"))
            {
                while (!(xml.isEndElement() &&
                         xml.name() == QLatin1String("HeartRateBpm")))
                {
                    xml.readNext();

                    if (xml.isStartElement() &&
                        xml.name() == QLatin1String("Value"))
                    {
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
            else if (xml.name() == QLatin1String("Position"))
            {
                GeoPoint gps;

                while (!(xml.isEndElement() &&
                         xml.name() == QLatin1String("Position")))
                {
                    xml.readNext();

                    if (!xml.isStartElement())
                        continue;

                    if (xml.name() == QLatin1String("LatitudeDegrees"))
                    {
                        gps.latitude =
                            xml.readElementText().toDouble();
                    }
                    else if (xml.name() == QLatin1String("LongitudeDegrees"))
                    {
                        gps.longitude =
                            xml.readElementText().toDouble();
                    }
                }

                sample.addValue(
                    TelemetryValueName::GPS,
                        gps,
                    Unit::None,
                    TelemetryValueType::GeoLocation);
            }

            //
            // Extensions / TPX
            //
            else if (xml.name() == QLatin1String("Speed"))
            {
                sample.addValue(
                    TelemetryValueName::Speed,
                    xml.readElementText().toDouble() * 3.6,
                    Unit::KilometerPerHour,
                    TelemetryValueType::Double);
            }
        }

        track.addSample(sample);
    }

    return !xml.hasError();
}
