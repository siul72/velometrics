#pragma once

#include <QSlider>

class RangeSlider : public QSlider
{
    Q_OBJECT

public:
    explicit RangeSlider(QWidget* parent = nullptr);

    int rangeStart() const;
    int rangeEnd() const;

public slots:
    void setRangeStart(int value);
    void setRangeEnd(int value);

    signals:
        void rangeChanged(int start, int end);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    int valueToPixel(int value) const;
    int pixelToValue(int x) const;

private:
    int m_rangeStart{0};
    int m_rangeEnd{100};
};