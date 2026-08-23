#pragma once
#include <QGraphicsScene>

#include "../common/ElementType.h"

class CanvasScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CanvasScene(QObject* parent = nullptr);
    void addElement(ElementType type);

};