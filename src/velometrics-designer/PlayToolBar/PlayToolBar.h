 #pragma once

# include <QWidget>

 class QLabel;
 class QSlider;

class PlayToolBar : public QWidget{
 Q_OBJECT

public:
 explicit PlayToolBar(QWidget* parent = nullptr);

 signals:
     void playRequested();
     void pauseRequested();
     void stopRequested();
     void seekRequested(qsizetype position);

public slots:
    void setPosition(qsizetype position) const;
    void onActivityLoaded(qsizetype numSamples) const;
    void setTimestamp(const QDateTime& timestamp) const;

private:
 QAction* m_playAction{};
 QAction* m_pauseAction{};
 QAction* m_stopAction{};

 QSlider* m_slider{};
 QLabel* m_timestampLabel{};
};

