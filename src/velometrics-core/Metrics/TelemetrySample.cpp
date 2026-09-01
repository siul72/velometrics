
#include "TelemetrySample.h"


void TelemetrySample::addValue(const TelemetryValueName telemetry_value_name, double value, const Unit unit,
    TelemetryValueType type)
{
    v = SampleValue{.name = telemetry_value_name, .value = value, .unit = unit};
    values.insert(telemetry_value_name, v);
}
