//
// Created by jenkins on 9/1/26.
//

#include "TelemetryTrack.h"

QDateTime TelemetryTrack::startTime() const
{
    if (samples.isEmpty()) {
        return {};
    }
    return samples.first().timestamp;
}

QDateTime TelemetryTrack::endTime() const
{
    if (samples.isEmpty()) {
        return {};
    }
    return samples.last().timestamp;
}

qint64 TelemetryTrack::durationMs() const
{
    return startTime().msecsTo(endTime());
}

qint64 TelemetryTrack::currentPositionMs()
{
    return 0;
}

ExportRange TelemetryTrack::exportRange()
{
    return {};
}

const TelemetrySample* TelemetryTrack::sampleAt(const qint64 timestampMs) const
{
    if (samples.isEmpty()) {
        return nullptr;
    }

    auto it = std::lower_bound(samples.begin(), samples.end(), timestampMs,
        [](const TelemetrySample& sample, qint64 timestamp) {
            return sample.timestamp.toMSecsSinceEpoch() < timestamp;
        });

    if (it != samples.end() && it->timestamp.toMSecsSinceEpoch() == timestampMs) {
        return &(*it);
    }

    return nullptr;
}

void TelemetryTrack::clear(){
    samples.clear();
}

bool TelemetryTrack::addSample(const TelemetrySample& sample){
    if (samples.isEmpty() || sample.timestamp > samples.last().timestamp){
        samples.append(sample);
        return true;
    }
    else{
        // Insert in sorted order
        auto it = std::lower_bound(samples.begin(), samples.end(), sample,
            [](const TelemetrySample& a, const TelemetrySample& b) {
                return a.timestamp < b.timestamp;
            });
        samples.insert(it, sample);
        return true;
    }
}

void TelemetryTrack::setCurrentPositionMs(qint64 pos)
{
}

void TelemetryTrack::setExportRange(const ExportRange& range)
{
}
