#include "CanvasScene.h"

#include <qfile.h>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QKeyEvent>
#include  <QGraphicsSceneMouseEvent>
#include  <QFileDialog>
#include <QDir>
#include <QStandardPaths>


#include "../common/ElementDefinition.h"
#include "../Elements/TelemetryWidgetItem.h"

CanvasScene::CanvasScene(QObject* parent): QGraphicsScene(parent){

    m_config = VelometricsSettings::instance();
    setSceneRect(0.0,0.0,m_config.canvasWidth,m_config.canvasHeight);
    setBackgroundBrush(m_config.canvasBackgroundColor);
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
    qDebug() << "Adding element: "<< elementTypeToString(element) << " units:" << def.defaultUnits;
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

void CanvasScene::removeSelectedItems() {
    for (const auto items = selectedItems(); QGraphicsItem* item : items)
    {
        removeItem(item);
        delete item;
    }
}

void CanvasScene::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Delete)
    {
        removeSelectedItems();
        return;
    }

    QGraphicsScene::keyPressEvent(event);
}

void CanvasScene::alignTop() const
{
    const auto items = selectedItems();
    if (items.size() < 2)
        return;
    const qreal topY = items.first()->pos().y();
    for (int i = 1; i < items.size(); ++i) {
        auto* item = items[i];
        item->setPos( item->pos().x(), topY);
    }
}

void CanvasScene::matchSize() const {
    const auto items = selectedItems();
    if (items.size() < 2)
        return;
    const auto* reference = dynamic_cast<TelemetryWidgetItem*>(items.first());
    if (!reference)
        return;
    const QSizeF targetSize = reference->size();
    for (int i = 1; i < items.size(); ++i) {
        auto* widget = dynamic_cast<TelemetryWidgetItem*>(items[i]);
        if (!widget)
            continue;
        widget->setSize(targetSize);
    }
}

void CanvasScene::distributeHorizontally() const
{
    auto items = selectedItems();

    if (items.size() < 3)
        return;

    std::ranges::sort(items,
                      [](QGraphicsItem* a, QGraphicsItem* b) {
                          return a->sceneBoundingRect().left()
                              < b->sceneBoundingRect().left();
                      });

    qreal totalWidth = 0.0;

    for (const auto* item : items)
        totalWidth += item->sceneBoundingRect().width();

    const qreal left = items.first()->sceneBoundingRect().left();
    const qreal right = items.last()->sceneBoundingRect().right();
    const qreal freeSpace = right - left - totalWidth;
    const qreal gap = freeSpace / (items.size() - 1);

    qreal currentX = left;

    for (auto* item : items)
    {
        QRectF rect = item->sceneBoundingRect();

        item->moveBy(
            currentX - rect.left(),
            0.0);

        currentX += rect.width() + gap;
    }
}

void CanvasScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event){
    // Ignore*double-clicks on widgets/items
    if (items(event->scenePos()).isEmpty()){
         QGraphicsScene::mouseDoubleClickEvent(event);
         return;
     }

    const QString fileName =
          QFileDialog::getOpenFileName(
            nullptr,
              tr("Select Background Image"),
             QString(),
              tr("Images *.png *.jpg *.jpeg *.bmp *.gif)"));

      if (!fileName.isEmpty()){
          m_backgroundImage.load(fileName);
          update();
      }

     QGraphicsScene::mouseDoubleClickEvent(event);
}

void CanvasScene::drawBackground(QPainter* painter,const QRectF& rect){
    QGraphicsScene::drawBackground(painter, rect);

    if (!m_backgroundImage.isNull())
    {
        painter->drawPixmap(
            sceneRect().toRect(),
            m_backgroundImage,
            m_backgroundImage.rect());
    }
}





