#pragma once
#include <QObject>
#include <QTimer>
#include "Activities/TCXLoader.h"
#include "Metrics/TelemetryTrack.h"
#include "../velometrics-designer/Canvas/CanvasScene.h"

class ActivityManager;


class VelometricsCore : public QObject {
    Q_OBJECT

public:
    static VelometricsCore& instance();
    VelometricsCore(const VelometricsCore&) = delete;
    VelometricsCore& operator=(const VelometricsCore&) = delete;

    template<typename Loader> bool loadActivity(const QString& fileName) {
        auto ret = Loader::load(fileName, m_activity);
        if (ret) {
            emit activityLoaded(m_activity.samples.count());
            this->startTimer();
        }
        return ret;
    }
    [[nodiscard]] const TelemetryTrack& getTelemetryTrack() const {
        return m_activity;
    }
    [[nodiscard]] QDateTime timestampAt(int index) const;

    void setCurrentIndex(const int index){
        m_currentSampleIndex = index;
    }

    void setCanvasScene(CanvasScene* scene){
        m_scene = scene;
    }

    signals:
        void activityLoaded(qsizetype numSamples);
        void sampleChanged(const TelemetrySample& sample);
        void playbackPositionChanged(qsizetype position);
        void timestampChanged(QDateTime timestamp);

    public slots:
        void play();
        void pause();
        void stop();
        void seek(int position);
        void setRenderBoundary(int start, int end);
        void render() const;
        void setPlaybackPosition(qsizetype index);

private:
    explicit VelometricsCore(QObject* parent = nullptr);
    TcxLoader m_tcx_activity{};
    TelemetryTrack m_activity{};
    QTimer m_timer;
    qsizetype m_currentSampleIndex {0};
    qsizetype m_start_render_index {0};
    qsizetype m_end_render_index {0};
    CanvasScene* m_scene {nullptr};

private slots:
    void startTimer();
    void stopTimer();
    void onTimerTimeout();

};
