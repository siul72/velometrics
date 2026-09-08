#pragma once
#include <QMetaType>
#include <QVariant>

enum class Unit
{
    None,
    Meter,
    Kilometer,
    MeterPerSecond,
    KilometerPerHour,
    BPM,
    Percent,
    Watt,
    Celsius, rpm
};

struct GeoPoint
{
    double latitude = 0.0;
    double longitude = 0.0;
};


Q_DECLARE_METATYPE(GeoPoint)

enum class TelemetryValueName{
    Altitude,
    Speed,
    HeartRate,
    Cadence,
    Power,
    Temperature,
    GPS, Distance
};

enum class TelemetryValueType
{
    Integer,
    Double,
    String,
    GeoLocation
};

using TelemetryVariant =  QVariant;

struct SampleValue
{
    TelemetryValueName name;
    QVariant value;
    Unit unit;
};




