
#include "RenderCanvasScene.h"
#include "../../velometrics-designer/Canvas/CanvasScene.h"
#include "../../velometrics-designer/Elements/TelemetryWidgetItem.h"
#include <QPainter>

RenderCanvasScene::RenderCanvasScene(QObject* parent) : QGraphicsScene(parent) {
    m_config = VelometricsSettings::instance();
    setSceneRect(0.0,0.0,m_config.canvasWidth,m_config.canvasHeight);
    setBackgroundBrush(m_config.canvasBackgroundColor);
}

void RenderCanvasScene::loadFrom(const CanvasScene* source){
    for (const auto& element : source->getTelemetryWidgets()){

        addItem(element);
    }
}


QImage RenderCanvasScene::renderFrame( const QSize& outputSize, const QColor& background) {
    QImage image(outputSize,QImage::Format_RGB32);
    image.fill(background);
    QPainter painter(&image);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    render(&painter,
        QRectF(QPointF(0, 0), outputSize),
        sceneRect());

    return image;
}

