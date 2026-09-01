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
    VelometricsConfiguration m_config{};

};