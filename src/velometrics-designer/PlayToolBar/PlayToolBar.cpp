
#include "PlayToolBar.h"

#include <QFileDialog>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <qstyle.h>

#include  "../../velometrics-core/VelometricsCore.h"


PlayToolBar::PlayToolBar(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QHBoxLayout(this);

    auto* playButton  = new QPushButton();
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    auto* pauseButton = new QPushButton();
    pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    auto* stopButton  = new QPushButton();
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    m_slider = new QSlider(Qt::Horizontal);
    m_timestampLabel = new QLabel("00:00:00");

    layout->addWidget(playButton);
    layout->addWidget(pauseButton);
    layout->addWidget(stopButton);
    layout->addWidget(m_slider, 1);
    layout->addWidget(m_timestampLabel);

    connect(playButton, &QPushButton::clicked, this, &PlayToolBar::playRequested);
    connect(pauseButton, &QPushButton::clicked, this, &PlayToolBar::pauseRequested);
    connect(stopButton, &QPushButton::clicked, this, &PlayToolBar::stopRequested);
    connect(m_slider, &QSlider::sliderReleased, this, [this](){emit seekRequested(m_slider->value());});
    connect(m_slider, &QSlider::sliderPressed, this, [this](){emit pauseRequested();});
}

void PlayToolBar::setPosition(const qsizetype position) const{
    m_slider->setValue(static_cast<int>(position));
}

void PlayToolBar::onActivityLoaded(const qsizetype numSamples) const {
    m_slider->setMaximum(static_cast<int>(numSamples));
}

void PlayToolBar::setTimestamp(const QDateTime& timestamp) const{
    m_timestampLabel->setText(timestamp.time().toString("hh:mm:ss"));
    //m_timestampLabel->update();
}
