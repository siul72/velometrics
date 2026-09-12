#pragma once
#include <QGraphicsView>

#include "../common/ElementType.h"

class CanvasScene;


class CanvasWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget* parent = nullptr);

    [[nodiscard]] CanvasScene* getScene() const {
        return m_scene;
    }

public slots:
    void addElement(ElementType type) const;

protected:

    void resizeEvent(QResizeEvent* event) override;



private:
    CanvasScene* m_scene {};
};
