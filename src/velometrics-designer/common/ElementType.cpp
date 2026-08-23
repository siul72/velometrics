//
// Created by jenkins on 8/23/26.
//
#include "ElementType.h"

#include <QString>

QString elementTypeToString(const ElementType type)
{
    switch (type)
    {
    case ElementType::Speed:
        return "Speed";

    case ElementType::HeartRate:
        return "Heart Rate";

    case ElementType::Power:
        return "Power";

    case ElementType::Cadence:
        return "Cadence";

    case ElementType::Distance:
        return "Distance";

    case ElementType::Elevation:
        return "Elevation";

    case ElementType::Text:
        return "Text";

    case ElementType::Image:
        return "Image";

    case ElementType::Rectangle:
        return "Rectangle";

    default:
        return "Unknown";
    }
}

ElementType stringToElementType(const QString& value)
{
    if (value == "Speed")
        return ElementType::Speed;

    if (value == "Heart Rate")
        return ElementType::HeartRate;

    if (value == "Power")
        return ElementType::Power;

    if (value == "Cadence")
        return ElementType::Cadence;

    if (value == "Distance")
        return ElementType::Distance;

    if (value == "Elevation")
        return ElementType::Elevation;

    if (value == "Text")
        return ElementType::Text;

    if (value == "Image")
        return ElementType::Image;

    if (value == "Rectangle")
        return ElementType::Rectangle;

    return ElementType::Unknown;
}
