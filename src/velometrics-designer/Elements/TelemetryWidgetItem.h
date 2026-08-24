#pragma once
#include <qgraphicsitem.h>

#include <QString>
#include "../common/ElementDefinition.h"

enum class Handle
{
    None,
    BottomRight
};

class TelemetryWidgetItem : public QGraphicsObject {
    Q_OBJECT
public:
    explicit TelemetryWidgetItem(ElementDefinition  definition, QGraphicsItem *parent = nullptr);

    bool showLabel = true;
    bool showBackground = true;

    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;
    [[nodiscard]] QRectF resizeHandle() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    QSizeF m_size { 1200, 600 };
    QRectF m_boundingRect;
    QColor m_backgroundColor = QColor(200,200,200);
    QString m_previewValue = "38";
    ElementDefinition m_definition;
    Handle m_activeHandle = Handle::None;
    QPointF m_resizeStartPos;
    QSizeF m_resizeStartSize;

};


