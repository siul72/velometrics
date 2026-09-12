#pragma once
#include <QGraphicsScene>
#include "../common/ElementType.h"
#include "../common/VeloMetricsConfig.h"

class CanvasScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CanvasScene(QObject* parent = nullptr);
    void addElement(ElementType element);
    void setHelpersVisible(bool visible);
    VelometricsConfiguration m_config{};

    QImage renderFrame( const QSize& outputSize, const QColor& background = Qt::black);

private:
    QGraphicsRectItem* m_border = nullptr;
    QList<QGraphicsLineItem*> m_gridLines;

};


