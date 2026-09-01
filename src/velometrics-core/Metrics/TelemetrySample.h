#pragma once
#include <qdatetime.h>
#include "../Metrics/Telemetry.h"


class TelemetrySample
{
    public:

    QDateTime timestamp;
    QMap<TelemetryValueName, SampleValue> values;
    void addValue(
                    TelemetryValueName telemetry_value_name,
                    double value,
                    Unit unit,
                    TelemetryValueType type);
};





