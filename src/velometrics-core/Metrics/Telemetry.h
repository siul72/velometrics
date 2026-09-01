#pragma once
#include <qdatetime.h>

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

using TelemetryVariant = std::variant<
    int,
    double,
    QString,
    GeoPoint
>;

struct SampleValue
{
    TelemetryValueName name;
    TelemetryVariant value;
    Unit unit;
};




