//
// Created by jenkins on 8/24/26.
//

#ifndef VELOMETRICS_ELEMENTDEFINITION_H
#define VELOMETRICS_ELEMENTDEFINITION_H
#include "ElementType.h"

struct ElementDefinition
{
    ElementType type;
    QString name;
    QString defaultUnits;
    QString iconPath;

    bool showIcon;
    bool showValue;
    bool showUnits;
};

static const QHash<ElementType, ElementDefinition> elementDefinitions =
{
    {
        ElementType::Speed,
        {
            ElementType::Speed,
            "Speed",
            "km/h",
            ":/icons/speed.svg",
            true,
            true,
            true
        }
    },

    {
        ElementType::Distance,
        {
            ElementType::Distance,
            "Distance",
            "km",
            ":/icons/distance.svg",
            true,
            true,
            true
        }
    },

    {
        ElementType::Gradient,
        {
            ElementType::Gradient,
            "Gradient",
            "%",
            ":/icons/gradient.svg",
            true,
            true,
            true
        }
    }
};

#endif //VELOMETRICS_ELEMENTDEFINITION_H
