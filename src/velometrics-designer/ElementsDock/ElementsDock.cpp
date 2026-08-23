
#include "ElementsDock.h"

#include <QListWidget>
#include <QTreeWidget>

#include "../common/ElementType.h"


ElementsDock::ElementsDock(QWidget* parent)
    : QDockWidget("Elements", parent)
{
    m_tree = new QTreeWidget(this);

    m_tree->setHeaderHidden(true);

    setWidget(m_tree);

    buildTree();

    connect(
        m_tree,
        &QTreeWidget::itemDoubleClicked,
        this,
        &ElementsDock::onItemDoubleClicked);
}

void ElementsDock::buildTree() const
{
    auto* metrics =
        new QTreeWidgetItem({"Metrics"});

    metrics->addChild(
        new QTreeWidgetItem({"Speed"}));

    metrics->addChild(
        new QTreeWidgetItem({"Heart Rate"}));

    metrics->addChild(
        new QTreeWidgetItem({"Power"}));

    metrics->addChild(
        new QTreeWidgetItem({"Cadence"}));

    metrics->addChild(
        new QTreeWidgetItem({"Distance"}));

    metrics->addChild(
        new QTreeWidgetItem({"Elevation"}));

    auto* graphics =
        new QTreeWidgetItem({"Graphics"});

    graphics->addChild(
        new QTreeWidgetItem({"Text"}));

    graphics->addChild(
        new QTreeWidgetItem({"Image"}));

    graphics->addChild(
        new QTreeWidgetItem({"SVG"}));

    graphics->addChild(
        new QTreeWidgetItem({"Rectangle"}));

    m_tree->addTopLevelItem(metrics);
    m_tree->addTopLevelItem(graphics);

    metrics->setExpanded(true);
    graphics->setExpanded(true);
}

void ElementsDock::onItemDoubleClicked( const QTreeWidgetItem* item, int) {
    if (!item)
        return;

    // Ignore categories
    if (item->childCount() > 0)
        return;
    const ElementType elementType = stringToElementType(item->text(0));
    emit elementRequested(elementType);
}