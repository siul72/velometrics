# pragma once
#include <QObject>
#include <QGraphicsScene>
#include "../../velometrics-designer/common/VeloMetricsConfig.h"

class CanvasScene;

class RenderCanvasScene : public QGraphicsScene{
public:
    explicit RenderCanvasScene(QObject* parent = nullptr);
    void loadFrom(const CanvasScene* source);
    QImage renderFrame( const QSize& outputSize, const QColor& background = Qt::black);

private:
    VelometricsConfiguration m_config{};
};
