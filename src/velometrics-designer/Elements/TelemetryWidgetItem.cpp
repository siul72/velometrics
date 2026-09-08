#include "TelemetryWidgetItem.h"

#include <qcursor.h>
#include <qpainter.h>
#include <utility>
#include<QGraphicsSceneMouseEvent>
#include "../common/ElementDefinition.h"
#include "../common/VeloMetricsConfig.h"
#include "../../velometrics-core/Metrics/TelemetrySample.h"
#include  "../../velometrics-core/VelometricsCore.h"


TelemetryWidgetItem::TelemetryWidgetItem(ElementDefinition  definition, QGraphicsItem* parent) :
QGraphicsObject(parent),  m_definition(std::move(definition)){
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
    m_boundingRect = QRectF(0, 0, m_size.width(), m_size.height());

    connect(&VelometricsCore::instance(), &VelometricsCore::sampleChanged,
        this, &TelemetryWidgetItem::onSampleChanged);
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


    const int valueFontSize = std::max(12, static_cast<int>(m_boundingRect.height() * 0.30));

    const int unitFontSize = std::max(8, static_cast<int>(valueFontSize * 0.45));

    QFont valueFont;
    valueFont.setBold(true);
    valueFont.setPixelSize(valueFontSize);

    QFont unitFont;
    unitFont.setPixelSize(unitFontSize);

    const QFontMetrics valueFm(valueFont);
    const QFontMetrics unitFm(unitFont);

    const QString value = m_value;
    const QString units = m_definition.defaultUnits;

    const int valueWidth = valueFm.horizontalAdvance(value);
    const int unitWidth  = unitFm.horizontalAdvance(units);

    const int spacing = valueFontSize / 5;
    const int totalWidth = valueWidth + spacing + unitWidth;

    const double x = (m_boundingRect.width() - totalWidth) / 2.0;
    const double y = m_boundingRect.height() / 2.0;

    painter->setPen(Qt::white);

    // Draw value
    painter->setFont(valueFont);
    painter->drawText(QPointF(x, y),value);

    // Draw units
    painter->setFont(unitFont);
    painter->drawText(QPointF(x + valueWidth + spacing,y), units);

    if (isSelected()) {
        painter->save();

        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(Qt::black, 2, Qt::DashLine));

        // Slightly inset the border
        const QRectF borderRect = boundingRect().adjusted(1, 1, -1, -1);
        painter->drawRect(borderRect);

        painter->setBrush(Qt::white);
        painter->setPen(QPen(Qt::cyan, 2));
        painter->drawRect(resizeHandle());

        painter->restore();
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

const TelemetryValueName* telemetryValueNameFromElementType(ElementType type)
{
    static const QHash<ElementType, TelemetryValueName> map = {
        {ElementType::Speed,      TelemetryValueName::Speed},
        {ElementType::HeartRate,  TelemetryValueName::HeartRate},
        {ElementType::Power,      TelemetryValueName::Power},
        {ElementType::Cadence,    TelemetryValueName::Cadence},
        {ElementType::Elevation,  TelemetryValueName::Altitude},
        {ElementType::Distance,   TelemetryValueName::Distance}
    };

    auto it = map.find(type);
    return it != map.end() ? &it.value() : nullptr;
}


void TelemetryWidgetItem::onSampleChanged(const TelemetrySample& sample) {
    const auto& sample_type = telemetryValueNameFromElementType(m_definition.type);
    const auto* sample_value = sample.get(*sample_type);
    setVisible(sample_value != nullptr);
    if (!sample_value) {
        hide();
        return;
    }

    switch (sample_value->value.typeId()) {
        case QMetaType::Double:
        case QMetaType::Float:
            m_value = QString::number(
                sample_value->value.toDouble(), 'f', 1);
            break;

        default:
            m_value = sample_value->value.toString();
            break;
    }

    update();
}
