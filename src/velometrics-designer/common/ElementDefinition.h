#pragma once

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
            .type = ElementType::Distance,
            .name = "Distance",
            .defaultUnits = "m",
            .iconPath = ":/icons/distance.svg",
            .showIcon = true,
            .showValue = true,
            .showUnits = true
        }
    },

    {
        ElementType::Gradient,
        {
            .type = ElementType::Gradient,
            .name = "Gradient",
            .defaultUnits = "%",
            .iconPath = ":/icons/gradient.svg",
            .showIcon = true,
            .showValue = true,
            .showUnits = true
        }
    }
};

