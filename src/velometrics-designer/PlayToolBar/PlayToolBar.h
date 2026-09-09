 #pragma once
#include <QPushButton>
# include <QWidget>
#include "../RangeSlider/RangeSlider.h"

 class QLabel;


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

 RangeSlider* m_slider{};
 QLabel* m_timestampLabel{};

 QPushButton* m_markInButton;
 QPushButton* m_markOutButton;

 QLabel* m_startLabel{};
 QLabel* m_endLabel{};
 static void updateTimeLabel(QLabel* label, int position);

private slots:
   void onMarkInClicked() const;
   void onMarkOutClicked() const;
};

