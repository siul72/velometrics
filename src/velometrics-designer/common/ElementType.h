#pragma once


#include <QString>

enum class ElementType
{
    // Telemetry
    Cadence,
    Distance,
    Elevation,
    Gradient,
    HeartRate,
    Power,
    Speed,

    // Maps
    MiniMap,
    FullRouteMap,
    PositionMarker,
    RouteTrace,

    // Charts
    SpeedChart,
    ElevationProfile,
    HeartRateChart,
    Unknown
};

QString elementTypeToString(ElementType type);
ElementType stringToElementType(const QString& value);

