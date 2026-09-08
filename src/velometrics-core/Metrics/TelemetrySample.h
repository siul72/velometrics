#pragma once
#include <QDateTime>
#include "../Metrics/Telemetry.h"



class TelemetrySample
{


    public:

    QDateTime timestamp;
    QMap<TelemetryValueName, SampleValue> values;
    void addValue(
                    TelemetryValueName telemetry_value_name,
                    TelemetryVariant value,
                    Unit unit,
                    TelemetryValueType type);
    [[nodiscard]] const SampleValue* get(TelemetryValueName name) const;

};





