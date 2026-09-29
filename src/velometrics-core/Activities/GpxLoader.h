#pragma once

#include <QString>

class TelemetryTrack;

class GpxLoader
{
public:
    static bool load(const QString& filename, TelemetryTrack& track);

private:
    static void calculateDerivedMetrics(TelemetryTrack& track);
};