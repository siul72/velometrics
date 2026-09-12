#include "CanvasScene.h"
#include <QGraphicsTextItem>
#include <QPainter>

#include "../common/ElementDefinition.h"
#include "../Elements/TelemetryWidgetItem.h"

CanvasScene::CanvasScene(QObject* parent): QGraphicsScene(parent){

    m_config = VelometricsSettings::instance();
    setSceneRect(0.0,0.0,m_config.canvasWidth,m_config.canvasHeight);
    setBackgroundBrush(Qt::white);
    //grid
    m_border = addRect(sceneRect(), QPen(Qt::black, 2));
    QPen gridPen(QColor(225, 225, 225));
    gridPen.setWidth(1);
    for (int x = 0; x <= m_config.canvasWidth; x += m_config.gridSize){
        m_gridLines.append(
            addLine(x, 0, x, m_config.canvasHeight, gridPen));
    }
    for (int y = 0; y <= m_config.canvasHeight; y += m_config.gridSize){
        m_gridLines.append(
            addLine(0, y, m_config.canvasWidth, y, gridPen));
    }
}

void CanvasScene::addElement(const ElementType element) {
    const auto def =  elementDefinitions.value(element);
    auto* widget = new TelemetryWidgetItem(def);
    widget->setPos(100, 100);
    addItem(widget);
}

QImage CanvasScene::renderFrame( const QSize& outputSize, const QColor& background) {
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

void CanvasScene::setHelpersVisible(const bool visible){
    if (m_border)
        m_border->setVisible(visible);

    if (visible){
        setBackgroundBrush(Qt::white);
    } else
    {
        setBackgroundBrush(Qt::black);
    }

    for (auto* line : m_gridLines)
        line->setVisible(visible);
}



