#include "CanvasScene.h"
#include <QGraphicsTextItem>
#include "../common/ElementDefinition.h"
#include "../Elements/TelemetryWidgetItem.h"

CanvasScene::CanvasScene(QObject* parent): QGraphicsScene(parent){
    constexpr double CanvasWidth = 3840.0;
    constexpr double CanvasHeight = 2160.0;

    setSceneRect(0.0,0.0,CanvasWidth,CanvasHeight);
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
    constexpr int GridSize = 50;
    auto gridPen = QPen(QColor(225, 225, 225));
    gridPen.setWidth(1);

    for (int x = 0; x <= CanvasWidth; x += GridSize){
        addLine(x,0,x,CanvasHeight,gridPen);
    }

    for (int y = 0; y <= CanvasHeight; y += GridSize){
        addLine(0,y,CanvasWidth,y, gridPen);
    }
}

void CanvasScene::addElement(const ElementType element) {
    const auto def =  elementDefinitions.value(element);
    auto* widget = new TelemetryWidgetItem(def);
    widget->setPos(100, 100);
    addItem(widget);
}

