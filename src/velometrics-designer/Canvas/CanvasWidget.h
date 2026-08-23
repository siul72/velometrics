#pragma once
#include <QGraphicsView>
#include "../common/ElementType.h"

class CanvasScene;

class CanvasWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget* parent = nullptr);

public slots:
    void addElement(ElementType type) const;

protected:

    void resizeEvent(QResizeEvent* event) override;

private:
    CanvasScene* m_scene {};
};
