
#include "TelemetrySample.h"

#include <utility>


void TelemetrySample::addValue(const TelemetryValueName telemetry_value_name, TelemetryVariant value, const Unit unit,
    TelemetryValueType type)
{
    const auto v = SampleValue{.name = telemetry_value_name, .value = std::move(value), .unit = unit};
    values.insert(telemetry_value_name, v);
}

const SampleValue* TelemetrySample::get(const TelemetryValueName name) const {
    const auto it = values.constFind(name);
    return it != values.constEnd() ? &it.value() : nullptr;
}
