
#include "PlayToolBar.h"

#include <QFileDialog>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <qstyle.h>

#include  "../../velometrics-core/VelometricsCore.h"


PlayToolBar::PlayToolBar(QWidget* parent): QWidget(parent){

    auto* playButton  = new QPushButton();
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    auto* pauseButton = new QPushButton();
    pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    auto* stopButton  = new QPushButton();
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    m_slider = new RangeSlider();
    m_timestampLabel = new QLabel("00:00:00");
    m_startLabel = new QLabel("00:00:00");
    m_endLabel = new QLabel("00:00:00");
    m_markInButton = new QPushButton("[", this);
    m_markOutButton = new QPushButton("]", this);
    //m_markInButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
    //m_markOutButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));

    auto* mainLayout = new QVBoxLayout(this);

    auto* controlsLayout = new QHBoxLayout();
    auto* timelineLayout = new QHBoxLayout();

    controlsLayout->addWidget(playButton);
    controlsLayout->addWidget(pauseButton);
    controlsLayout->addWidget(stopButton);
    controlsLayout->addSpacing(20);
    controlsLayout->addWidget(m_markInButton);
    controlsLayout->addWidget(m_markOutButton);
    controlsLayout->addStretch();
    controlsLayout->addWidget(m_timestampLabel);

    timelineLayout->addWidget(m_startLabel);
    timelineLayout->addWidget(m_slider, 1);
    timelineLayout->addWidget(m_endLabel);

    mainLayout->addLayout(controlsLayout);
    mainLayout->addLayout(timelineLayout);

    connect(playButton, &QPushButton::clicked, this, &PlayToolBar::playRequested);
    connect(pauseButton, &QPushButton::clicked, this, &PlayToolBar::pauseRequested);
    connect(stopButton, &QPushButton::clicked, this, &PlayToolBar::stopRequested);
    connect(m_slider, &QSlider::sliderReleased, this, [this](){emit seekRequested(m_slider->value());});
    connect(m_slider, &QSlider::sliderPressed, this, [this](){emit pauseRequested();});
    connect(
    m_markInButton,
    &QPushButton::clicked,
    this,
    &PlayToolBar::onMarkInClicked);

    connect(
        m_markOutButton,
        &QPushButton::clicked,
        this,
        &PlayToolBar::onMarkOutClicked);
}

void PlayToolBar::setPosition(const qsizetype position) const{
    m_slider->setValue(static_cast<int>(position));
}

void PlayToolBar::onActivityLoaded(const qsizetype numSamples) const {
    const auto v = static_cast<int>(numSamples)-1;
    m_slider->setMaximum(v);
    m_slider->setRangeEnd(v);
}

void PlayToolBar::setTimestamp(const QDateTime& timestamp) const{
    m_timestampLabel->setText(timestamp.time().toString("hh:mm:ss"));
    //m_timestampLabel->update();
}


void PlayToolBar::onMarkInClicked() const {
    m_slider->setRangeStart(m_slider->value());
    updateTimeLabel(m_startLabel, m_slider->value());
}

void PlayToolBar::onMarkOutClicked() const {
    m_slider->setRangeEnd(m_slider->value());
    updateTimeLabel(m_endLabel, m_slider->value());
}

void PlayToolBar::updateTimeLabel(QLabel* label, const int position) {
    const QDateTime timestamp =
        VelometricsCore::instance().timestampAt(position);

    if (!timestamp.isValid())
        return;

    label->setText(timestamp.toString("hh:mm:ss"));
}


