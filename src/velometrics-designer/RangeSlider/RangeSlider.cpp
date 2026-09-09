#include "RangeSlider.h"

#include <QPainter>
#include <QMouseEvent>
#include <QStyle>
#include <QStyleOptionSlider>

RangeSlider::RangeSlider(QWidget* parent): QSlider(Qt::Horizontal, parent){
}

int RangeSlider::rangeStart() const {
    return m_rangeStart;
}

int RangeSlider::rangeEnd() const {
    return m_rangeEnd;
}

void RangeSlider::setRangeStart(int value) {

    value = qBound(minimum(), value, m_rangeEnd);
    if (m_rangeStart == value)
        return;
    m_rangeStart = value;
    emit rangeChanged(m_rangeStart, m_rangeEnd);
    update();
}

void RangeSlider::setRangeEnd(int value){
    value = qBound(m_rangeStart, value, maximum());
    if (m_rangeEnd == value)
        return;

    m_rangeEnd = value;
    emit rangeChanged(m_rangeStart, m_rangeEnd);
    update();
}

int RangeSlider::valueToPixel(const int value) const {
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    const QRect groove = style()->subControlRect(
        QStyle::CC_Slider,
        &opt,
        QStyle::SC_SliderGroove,
        this);

    const double ratio =
        static_cast<double>(value - minimum()) /
        static_cast<double>(maximum() - minimum());

    return groove.left() +
           static_cast<int>(ratio * groove.width());
}

int RangeSlider::pixelToValue(const int x) const {
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    const QRect groove = style()->subControlRect(
        QStyle::CC_Slider,
        &opt,
        QStyle::SC_SliderGroove,
        this);

    const double ratio =
        static_cast<double>(x - groove.left()) /
        groove.width();

    return minimum() +
           static_cast<int>(ratio * (maximum() - minimum()));
}

void RangeSlider::paintEvent(QPaintEvent* event) {
    QSlider::paintEvent(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    const QRect groove = style()->subControlRect(
        QStyle::CC_Slider,
        &opt,
        QStyle::SC_SliderGroove,
        this);

    const int startX = valueToPixel(m_rangeStart);
    const int endX = valueToPixel(m_rangeEnd);
    const int centerY = groove.center().y();

    //
    // Render region highlight
    //

    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 188, 212, 90));
    p.drawRect(
        QRect(
            startX,
            centerY - 4,
            endX - startX,
            8));

    //
    // Start marker
    //

    p.setPen(QPen(QColor(0x4CAF50), 2));

    p.drawLine(
        startX,
        0,
        startX,
        height());

    //
    // End marker
    //

    p.setPen(QPen(QColor(0xF44336), 2));

    p.drawLine(
        endX,
        0,
        endX,
        height());

    //
    // Small handles
    //

    p.setBrush(QColor(0x4CAF50));
    p.setPen(Qt::NoPen);
    p.drawEllipse(QPointF(startX, centerY), 4, 4);
    p.setBrush(QColor(0xF44336));
    p.drawEllipse(QPointF(endX, centerY), 4, 4);
}

void RangeSlider::mouseDoubleClickEvent(QMouseEvent* event){
    const int clickedValue =
        pixelToValue(static_cast<int>(event->position().x()));

    const int distToStart =
        qAbs(clickedValue - m_rangeStart);

    const int distToEnd =
        qAbs(clickedValue - m_rangeEnd);

    if (distToStart < distToEnd)
    {
        setRangeStart(clickedValue);
    }
    else
    {
        setRangeEnd(clickedValue);
    }

    QSlider::mouseDoubleClickEvent(event);
}