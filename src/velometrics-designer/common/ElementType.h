#pragma once


#include <QString>

enum class ElementType
{
    // Telemetry
    Speed,
    HeartRate,
    Power,
    Cadence,
    Gradient,
    Elevation,
    Distance,

    // Graphics
    Label,
    Text,
    Icon,
    Image,
    Rectangle,
    Circle,

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

