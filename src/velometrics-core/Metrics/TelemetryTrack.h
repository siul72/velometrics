#pragma once
#include <qglobal.h>
#include <QObject>

#include "Telemetry.h"
#include "TelemetrySample.h"
#include "../Metrics/Telemetry.h"

struct ExportRange
{
    qint64 startMs = 0;
    qint64 endMs = 0;
};

class TelemetryTrack : public QObject
{
    Q_OBJECT

public:
    QVector<TelemetrySample> samples;
    [[nodiscard]] QDateTime startTime() const;
    [[nodiscard]] QDateTime endTime() const;
    [[nodiscard]] qint64 durationMs() const;
    [[nodiscard]] static qint64 currentPositionMs();
    [[nodiscard]] static ExportRange exportRange();
    [[nodiscard]] const TelemetrySample* sampleAt(qint64 timestampMs) const;

    void clear();
    bool addSample(const TelemetrySample& sample);
    static void setCurrentPositionMs(qint64 pos);
    static void setExportRange(const ExportRange& range);

    signals:
        void positionChanged(qint64);
        void exportRangeChanged();
};


