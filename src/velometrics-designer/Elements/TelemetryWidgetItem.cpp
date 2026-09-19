#include "TelemetryWidgetItem.h"

#include <qcursor.h>
#include <qpainter.h>
#include <utility>
#include<QGraphicsSceneMouseEvent>
#include <QIcon>
#include <QRectF>

#include "../common/ElementDefinition.h"
#include "../common/VeloMetricsConfig.h"
#include "../../velometrics-core/Metrics/TelemetrySample.h"
#include  "../../velometrics-core/VelometricsCore.h"
#include "../../velometrics-core/Templates/ThemeTemplateManager.h"

TelemetryWidgetItem::TelemetryWidgetItem(ElementDefinition  definition, QGraphicsItem* parent) :
QGraphicsObject(parent),  m_definition(std::move(definition)){
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
    m_boundingRect = QRectF(0, 0, m_size.width(), m_size.height());
    m_icon = ThemeTemplateManager::instance().icon(elementTypeToString(definition.type));
    connect(&VelometricsCore::instance(), &VelometricsCore::sampleChanged,
            this, &TelemetryWidgetItem::onSampleChanged);


}

QRectF TelemetryWidgetItem::boundingRect() const{
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

    int icon_size = 0;
    const int elements_margin = static_cast<int>(std::ceil(m_boundingRect.height() * 0.15));
    if(m_definition.showIcon){
        icon_size = qRound(0.8 * qMin(m_boundingRect.width()-elements_margin,m_boundingRect.height()-elements_margin));
        const QRect iconRect(elements_margin, elements_margin, icon_size, icon_size);
        m_icon.paint(painter, iconRect);
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

    const double x = icon_size/0.8 + elements_margin + spacing;
    painter->setPen(Qt::white);

    // Draw value
    painter->setFont(valueFont);
    const QRectF valueRect(x,0,valueWidth,m_boundingRect.height());
    painter->drawText(valueRect, Qt::AlignVCenter | Qt::AlignRight,value);

    // Draw units
    painter->setFont(unitFont);
    const QRectF unitRect(x + valueWidth + unitWidth,0,unitWidth,m_boundingRect.height());
    painter->drawText(unitRect, Qt::AlignVCenter | Qt::AlignRight, units);

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

QString TelemetryWidgetItem::elementType() const {
    return elementTypeToString(m_definition.type);
}

QColor TelemetryWidgetItem::backgroundColor() const {
    return m_backgroundColor;
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
        {ElementType::Distance,   TelemetryValueName::Distance},
        {ElementType::Gradient,      TelemetryValueName::Gradient}
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
    //qDebug() << "widget updated " << m_value << " value";
    update();
}

QSizeF TelemetryWidgetItem::size() const {
        return m_boundingRect.size();
}

void TelemetryWidgetItem::setSize(const QSizeF& size) {
        prepareGeometryChange();
        m_boundingRect.setSize(size);
        update();
}

void TelemetryWidgetItem::serialize(QDataStream& stream) const {
    stream << static_cast<qint32>(m_definition.type);
    stream << pos();
    stream << m_size;
    stream << m_backgroundColor;
    stream << m_value;
    stream << showLabel;
    stream << showBackground;
}

void TelemetryWidgetItem::deserialize(QDataStream& stream) {
    QPointF position;

    stream >> position;
    stream >> m_size;
    stream >> m_backgroundColor;
    stream >> m_value;
    stream >> showLabel;
    stream >> showBackground;

    setPos(position);

    m_boundingRect = QRectF(
        QPointF(0, 0),
        m_size);

    update();
}

