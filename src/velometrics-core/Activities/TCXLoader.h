
#pragma once
#include <QString>

class TelemetryTrack;

class TcxLoader{
public:
    static bool load(const QString& filename,  TelemetryTrack& track);
};

