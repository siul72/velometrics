#include "VelometricsCore.h"

#include "Activities/TCXLoader.h"
#include "Rendering/VideoRenderService.h"

VelometricsCore& VelometricsCore::instance(){
    static VelometricsCore instance;
    return instance;
}

void VelometricsCore::play() {
    startTimer();
}

void VelometricsCore::pause(){
    stopTimer();
}

void VelometricsCore::stop() {
    stopTimer();
    m_currentSampleIndex = 0;
}

void VelometricsCore::seek(const int position){

    if (position >= m_activity.samples.size()) {
        return;
    }
    m_currentSampleIndex = position;
    if (!m_timer.isActive()){
        startTimer();
    }
}

void VelometricsCore::setRenderBoundary(const int start, const int end){
    m_start_render_index = start;
    m_end_render_index = end;
}

void VelometricsCore::render() const {
    VideoRenderService renderer;
    renderer.render(
        m_scene,
        static_cast<int>(m_start_render_index),
        static_cast<int>(m_end_render_index),
        "output.mp4");

}

VelometricsCore::VelometricsCore(QObject* parent) : QObject(parent) {

        connect(&m_timer,
                &QTimer::timeout,
                this,
                &VelometricsCore::onTimerTimeout);

}

void VelometricsCore::startTimer(){
   m_timer.start(1000);
}

void VelometricsCore::stopTimer(){
    m_timer.stop();
}

void VelometricsCore::onTimerTimeout(){

    if (m_currentSampleIndex >= m_activity.samples.size()) {
        stopTimer();
        return;
    }

    setPlaybackPosition(m_currentSampleIndex);
    ++m_currentSampleIndex;
}

void VelometricsCore::setPlaybackPosition(const qsizetype index){
    if (index < 0 || index >= m_activity.samples.size())
        return;

    m_currentSampleIndex = index;
    const auto sample = m_activity.samples[index];
    emit sampleChanged(sample);
    emit playbackPositionChanged(index);
    emit timestampChanged(sample.timestamp);
}

QDateTime VelometricsCore::timestampAt(const int index) const {
    if (index >= m_activity.samples.size()) {
        return {};
    }
    return m_activity.samples.at(index).timestamp;
}



