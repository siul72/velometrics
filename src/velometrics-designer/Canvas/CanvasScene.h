#pragma once
#include <QGraphicsScene>
#include "../common/ElementType.h"
#include "../common/VeloMetricsConfig.h"

class TelemetryWidgetItem;

class CanvasScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CanvasScene(QObject* parent = nullptr);
    void initHelpers();
    void addElement(ElementType element);
    [[nodiscard]] QList<TelemetryWidgetItem*> getTelemetryWidgets() const;
    void setHelpersVisible(bool visible);
    VelometricsConfiguration m_config{};
    QImage renderFrame( const QSize& outputSize, const QColor& background = Qt::black);

public slots:
    void removeSelectedItems();
    void keyPressEvent(QKeyEvent* event) override;
    void alignTop() const;
    void matchSize() const;
    void distributeHorizontally() const;
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void drawBackground(QPainter* painter, const QRectF& rect) override;

private:
    QGraphicsRectItem* m_border = nullptr;
    QList<QGraphicsLineItem*> m_gridLines;
    QPixmap m_backgroundImage;
    QList<TelemetryWidgetItem*> m_widgets;

};


