#include "TelemetryWidgetItem.h"

#include <qcursor.h>
#include <qpainter.h>

#include <utility>
#include<QGraphicsSceneMouseEvent>

#include "../common/ElementDefinition.h"

TelemetryWidgetItem::TelemetryWidgetItem(ElementDefinition  definition, QGraphicsItem* parent) :
QGraphicsObject(parent),  m_definition(std::move(definition)){
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptedMouseButtons(Qt::LeftButton);
    m_boundingRect = QRectF(0, 0, m_size.width(), m_size.height());
}

QRectF TelemetryWidgetItem::boundingRect() const
{
    return m_boundingRect;
}

void TelemetryWidgetItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*,QWidget*)
{

    painter->setRenderHint(QPainter::Antialiasing);

    if(showBackground){
        painter->setBrush(m_backgroundColor);
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(m_boundingRect, 10, 10);
    }

    if(m_definition.showIcon){
        painter->drawPixmap(10,10,24,24, m_definition.iconPath);
    }

    if(m_definition.showValue){
        painter->drawText(
            QRectF(0, 40, m_boundingRect.width(), 60),
            Qt::AlignCenter,
            m_previewValue);
    }

    if(m_definition.showUnits) {
        painter->drawText(
            QRectF(0, 100, m_boundingRect.width(), 20),
            Qt::AlignCenter,
            m_definition.defaultUnits);
    }

    if (isSelected())
    {
        painter->setPen(QPen(Qt::cyan, 20));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
        painter->setPen(Qt::black);
        painter->setBrush(Qt::white);
        painter->drawRect(resizeHandle());
    }

}

QRectF TelemetryWidgetItem::resizeHandle() const
{
    return {
        m_size.width() - 80,
        m_size.height() - 80,
        80,
        80};
}

void TelemetryWidgetItem::mousePressEvent(
    QGraphicsSceneMouseEvent* event)
{
    if (resizeHandle().contains(event->pos())){
        setFlag(QGraphicsItem::ItemIsMovable, false);
        m_activeHandle = Handle::BottomRight;
        m_resizeStartPos = event->pos();
        m_resizeStartSize = m_size;
        event->accept();
        return;
    }

    QGraphicsObject::mousePressEvent(event);
}

void TelemetryWidgetItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    if (m_activeHandle == Handle::BottomRight){
        //qDebug() << "RESIZING";
        const QPointF delta = event->pos() - m_resizeStartPos;
        prepareGeometryChange();

        m_size.setWidth(
            std::max(100.0,
                     m_resizeStartSize.width() + delta.x()));

        m_size.setHeight(
            std::max(80.0,
                     m_resizeStartSize.height() + delta.y()));

        setFlag(QGraphicsItem::ItemIsMovable, false);
        update();
        return;
    }

    QGraphicsObject::mouseMoveEvent(event);
}

void TelemetryWidgetItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    m_activeHandle = Handle::None;
    setFlag(QGraphicsItem::ItemIsMovable, true);
    QGraphicsObject::mouseReleaseEvent(event);
}

void TelemetryWidgetItem::hoverMoveEvent(
    QGraphicsSceneHoverEvent* event)
{
    if (resizeHandle().contains(event->pos()))
        setCursor(QCursor(Qt::SizeFDiagCursor));
    else
        setCursor(QCursor(Qt::ArrowCursor));
}
