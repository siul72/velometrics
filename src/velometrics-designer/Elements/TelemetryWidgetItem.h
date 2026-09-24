#pragma once
#include <qgraphicsitem.h>
#include <QIcon>

#include <QString>
#include "../common/ElementDefinition.h"
#include "../../velometrics-core/Metrics/TelemetrySample.h"

enum class Handle{
    None,
    BottomRight
};

#define FREE_STATE = 1
#define BUILDING_SQUARE = 2
#define BEGIN_SIDE_EDIT = 3
#define END_SIDE_EDIT = 4
#define CURSOR_ON_BEGIN_SIDE = 1
#define CURSOR_ON_END_SIDE = 2

class TelemetryWidgetItem : public QGraphicsObject {
    Q_OBJECT

public:
    explicit TelemetryWidgetItem(ElementDefinition  definition, QGraphicsObject *parent = nullptr);

    bool showLabel = true;
    bool showBackground = true;

    [[nodiscard]] QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    [[nodiscard]] QRectF resizeHandle() const;
    [[nodiscard]] QString elementType() const;
    [[nodiscard]] QColor backgroundColor() const;

public slots:
    void onSampleChanged(const TelemetrySample& sample);
    [[nodiscard]] QSizeF size() const;
    void setSize(const QSizeF& size);
    void serialize(QDataStream& stream) const;
    void deserialize(QDataStream& stream);
    void setBackgroundColor(const QColor& color);
    bool labelVisible() const;
    void setLabelVisible(bool visible);
    bool backgroundVisible() const;
    void setBackgroundVisible(bool visible);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
    QSizeF m_size { 1200, 600 };
    QRectF m_boundingRect;
    QColor m_backgroundColor = QColor(200,200,200);
    QString m_value = "38";
    ElementDefinition m_definition;
    Handle m_activeHandle = Handle::None;
    QPointF m_resizeStartPos;
    QSizeF m_resizeStartSize;
    bool m_resizing{};
    QIcon m_icon;

};


