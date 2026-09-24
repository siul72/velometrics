
#include "ElementType.h"

#include <QString>

QString elementTypeToString(const ElementType type)
{
    switch (type)
    {
    case ElementType::Speed:
        return "Speed";

    case ElementType::HeartRate:
        return "HeartRate";

    case ElementType::Power:
        return "Power";

    case ElementType::Cadence:
        return "Cadence";

    case ElementType::Distance:
        return "Distance";

    case ElementType::Elevation:
        return "Elevation";

    case ElementType::Gradient:
        return "Gradient";



    default:
        return "Unknown";
    }
}

ElementType stringToElementType(const QString& value)
{
    if (value == "Speed")
        return ElementType::Speed;

    if (value == "HeartRate")
        return ElementType::HeartRate;

    if (value == "Power")
        return ElementType::Power;

    if (value == "Cadence")
        return ElementType::Cadence;

    if (value == "Distance")
        return ElementType::Distance;

    if (value == "Elevation")
        return ElementType::Elevation;

    if (value == "Gradient")
        return ElementType::Gradient;


    return ElementType::Unknown;
}
