#include "VelometricsCore.h"

#include "Activities/TCXLoader.h"
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

    const auto& samples = m_activity.samples;

    if (m_currentSampleIndex >= samples.size()) {
        stopTimer();
        return;
    }

    const auto sample = samples[m_currentSampleIndex];

    emit sampleChanged(sample);
    emit playbackPositionChanged(m_currentSampleIndex);
    emit timestampChanged(sample.timestamp);
    ++m_currentSampleIndex;
}


