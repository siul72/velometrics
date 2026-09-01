#include "CanvasScene.h"
#include <QGraphicsTextItem>
#include "../common/ElementDefinition.h"
#include "../Elements/TelemetryWidgetItem.h"

CanvasScene::CanvasScene(QObject* parent): QGraphicsScene(parent){

    m_config = VelometricsSettings::instance();
    setSceneRect(0.0,0.0,m_config.canvasWidth,m_config.canvasHeight);
    //
    // White background
    //
    setBackgroundBrush(Qt::white);
    //
    // Canvas border
    //
    addRect(sceneRect(),QPen(Qt::black, 2));
    //
    // Grid
    //
    auto gridPen = QPen(QColor(225, 225, 225));
    gridPen.setWidth(1);

    for (int x = 0; x <= m_config.canvasWidth; x += m_config.gridSize){
        addLine(x,0,x,m_config.canvasHeight,gridPen);
    }

    for (int y = 0; y <= m_config.canvasHeight; y += m_config.gridSize){
        addLine(0,y,m_config.canvasWidth,y, gridPen);
    }
}

void CanvasScene::addElement(const ElementType element) {
    const auto def =  elementDefinitions.value(element);
    auto* widget = new TelemetryWidgetItem(def);
    widget->setPos(100, 100);
    addItem(widget);
}

