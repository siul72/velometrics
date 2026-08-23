#include "CanvasWidget.h"

#include "CanvasScene.h"

#include <QResizeEvent>


CanvasWidget::CanvasWidget(QWidget* parent)
    : QGraphicsView(parent)
{
    m_scene = new CanvasScene(this);

    setScene(m_scene);

    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::TextAntialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);

    setDragMode(QGraphicsView::RubberBandDrag);

    setTransformationAnchor(
        QGraphicsView::AnchorUnderMouse);

    setAlignment(
        Qt::AlignCenter);

    fitInView(
        m_scene->sceneRect(),
        Qt::KeepAspectRatio);
}

void CanvasWidget::resizeEvent(
    QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);

    fitInView(
        m_scene->sceneRect(),
        Qt::KeepAspectRatio);
}

void CanvasWidget::addElement(const ElementType type) const
{
    m_scene->addElement(type);

}
