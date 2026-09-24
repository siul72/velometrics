#pragma once

#include "ElementType.h"

struct ElementDefinition
{
    ElementType type;
    QString defaultUnits;
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
            "km/h",
            true,
            true,
            true
        }
    },
    {
        ElementType::Distance,
        {
            .type = ElementType::Distance,

            .defaultUnits = "m",
            .showIcon = true,
            .showValue = true,
            .showUnits = true
        }
    },
    {
        ElementType::Gradient,
        {
            .type = ElementType::Gradient,
             .defaultUnits = "%",
            .showIcon = true,
            .showValue = true,
            .showUnits = true
            }
    },
    {
        ElementType::HeartRate,
        {
            .type = ElementType::HeartRate,
             .defaultUnits = "bpm",
            .showIcon = true,
            .showValue = true,
            .showUnits = true
        }
    },
    {
        ElementType::Elevation,
        {
            .type = ElementType::Elevation,
             .defaultUnits = "m",
            .showIcon = true,
            .showValue = true,
            .showUnits = true
        }
    },
{
        ElementType::Power,
        {
            .type = ElementType::Power,
             .defaultUnits = "W",
            .showIcon = true,
            .showValue = true,
            .showUnits = true
        }

    },
};

