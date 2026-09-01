#include "TelemetryWidgetItem.h"

#include <qcursor.h>
#include <qpainter.h>
#include <utility>
#include<QGraphicsSceneMouseEvent>
#include "../common/ElementDefinition.h"
#include "../common/VeloMetricsConfig.h"



TelemetryWidgetItem::TelemetryWidgetItem(ElementDefinition  definition, QGraphicsItem* parent) :
QGraphicsObject(parent),  m_definition(std::move(definition)){
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
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

    if (isSelected()){

        painter->setPen(QPen(Qt::black, 4, Qt::DashLine));
        painter->drawRect(boundingRect());

        painter->setBrush(Qt::white);
        painter->setPen(QPen(Qt::cyan, 2));
        painter->drawRect(resizeHandle());
    }


}

QRectF TelemetryWidgetItem::resizeHandle() const
{
    return {
        m_size.width() - 40,
        m_size.height() - 40,
        40,
        40};
}


void TelemetryWidgetItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    m_resizing = false;
    qDebug() << "move true";
    setFlag(QGraphicsItem::ItemIsMovable, true);
    QGraphicsObject::mouseReleaseEvent(event);
}

void TelemetryWidgetItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event){
    if (resizeHandle().contains(event->pos())){
        setCursor(Qt::SizeHorCursor);
    }
    else{
        unsetCursor();
    }
    QGraphicsObject::hoverMoveEvent(event);
}

void TelemetryWidgetItem::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if (resizeHandle().contains(event->pos())){
        m_resizing = true;
        qDebug() << "move false";
        setFlag(QGraphicsItem::ItemIsMovable, false);
        event->accept();
        return;
    }
    QGraphicsObject::mousePressEvent(event);
}

void TelemetryWidgetItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    //qDebug() << "Mouse move" << m_resizing;
    if (m_resizing){
        prepareGeometryChange();

        const auto& cfg = VelometricsSettings::instance();

        const qreal width = cfg.snapToGrid
            ? snapToGrid(event->pos().x())
            : event->pos().x();

        const qreal height = cfg.snapToGrid
            ? snapToGrid(event->pos().y())
            : event->pos().y();

        m_size.setWidth(std::max(100.0,width));
        m_size.setHeight(std::max(100.0,height));

        m_boundingRect = QRectF(0,0, m_size.width(),m_size.height());

        update();
        event->accept();
        return;
    }

    QGraphicsObject::mouseMoveEvent(event);
}

QVariant TelemetryWidgetItem::itemChange(const GraphicsItemChange change, const QVariant& value)
{
    qDebug() << "Item change" << QString(value.toString());
    if (change == ItemPositionChange)
    {
        const auto& cfg = VelometricsSettings::instance();
        if (cfg.snapToGrid)
        {
            QPointF pos = value.toPointF();
            pos.setX(snapToGrid(pos.x()));
            pos.setY(snapToGrid(pos.y()));
            return pos;
        }
    }

    return QGraphicsObject::itemChange(change, value);
}
