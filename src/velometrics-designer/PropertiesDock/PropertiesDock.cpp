#include "PropertiesDock.h"
#include "../Elements/TelemetryWidgetItem.h"

#include <QTreeWidget>
#include <QVBoxLayout>
#include <QHeaderView>

PropertiesDock::PropertiesDock(QWidget* parent)
    : QDockWidget("Properties", parent)
{
    auto* container = new QWidget(this);

    m_propertyTree = new QTreeWidget;
    m_propertyTree->setColumnCount(2);
    m_propertyTree->setHeaderLabels(
        { "Property", "Value" });

    m_propertyTree->header()->setStretchLastSection(true);

    auto* layout = new QVBoxLayout(container);
    layout->addWidget(m_propertyTree);

    setWidget(container);

    connect(
        m_propertyTree,
        &QTreeWidget::itemChanged,
        this,
        &PropertiesDock::onItemChanged);
}

void PropertiesDock::loadProperties(TelemetryWidgetItem* item) {
    QSignalBlocker blocker(m_propertyTree);
    m_currentItem = item;
    m_propertyTree->clear();
    if (!item)
        return;

    auto* root = new QTreeWidgetItem(m_propertyTree);
    root->setText(0, item->elementType());

    auto addEditable = [] (QTreeWidgetItem* parent,
                      const QString& name,
                      const QString& value)
    {
        auto* child = new QTreeWidgetItem(parent);

        child->setText(0, name);
        child->setText(1, value);
        child->setFlags(child->flags() | Qt::ItemIsEditable);
        constexpr QColor bg(230, 245, 255); // light blue
        child->setBackground(0, bg);
        child->setBackground(1, bg);
        return child;
    };

    auto addReadOnly =
    [](QTreeWidgetItem* parent,
      const QString& name,
       const QString& value)
    {
        auto* child = new QTreeWidgetItem(parent);

        child->setText(0, name);
        child->setText(1, value);

        child->setFlags(child->flags() & ~Qt::ItemIsEditable);
        const QColor bg(245, 245, 245); // light gray
        child->setBackground(0, bg);
        child->setBackground(1, bg);
        return child;
    };

    //
    // Position
    //
    auto* positionGroup = new QTreeWidgetItem(root);
    positionGroup->setText(0, "Position");
    addEditable(positionGroup, "X", QString::number(item->pos().x()));
    addEditable(positionGroup,"Y", QString::number(item->pos().y()));

    //
    // Size
    //
    auto* sizeGroup = new QTreeWidgetItem(root);
    sizeGroup->setText(0, "Size");

    addEditable(sizeGroup,"Width",QString::number(item->size().width()));
    addEditable(sizeGroup,"Height",QString::number(item->size().height()));

    //
    // Appearance
    //
    auto* appearanceGroup = new QTreeWidgetItem(root);
    appearanceGroup->setText(0, "Appearance");

    addEditable(appearanceGroup,"BackgroundColor",item->backgroundColor().name());
    addEditable(appearanceGroup,"ShowLabel",item->showLabel ? "true" : "false");
    addEditable(appearanceGroup,"ShowBackground",item->showBackground ? "true" : "false");

    //
    // Premium features
    //
    auto* premiumGroup = new QTreeWidgetItem(root);
    premiumGroup->setText(0, "Premium");

    auto* fontFamily =
        addReadOnly(
            premiumGroup,
            "Font Family",
            "Segoe UI 🔒");

    fontFamily->setToolTip(
        1,
        "Premium feature. Upgrade to edit.");

    auto* fontSize =
        addReadOnly(
            premiumGroup,
            "Font Size",
            "24 🔒");

    fontSize->setToolTip(
        1,
        "Premium feature. Upgrade to edit.");

    auto* icon =
        addReadOnly(
            premiumGroup,
            "Icon",
            "Telemetry 🔒");

    icon->setToolTip(
        1,
        "Premium feature. Upgrade to edit.");

    root->setExpanded(true);
    positionGroup->setExpanded(true);
    sizeGroup->setExpanded(true);
    appearanceGroup->setExpanded(true);
    premiumGroup->setExpanded(true);
}

void PropertiesDock::onItemChanged(const QTreeWidgetItem* item, const int column) {

    if (m_updatingTree)
        return;

    if (!m_currentItem)
        return;

    if (column != 1)
        return;

    const QString property =
        item->text(0);

    const QString value =
        item->text(1);

    if (property == "X")
    {
        auto p = m_currentItem->pos();
        p.setX(value.toDouble());
        m_currentItem->setPos(p);
    }
    else if (property == "Y")
    {
        auto p = m_currentItem->pos();
        p.setY(value.toDouble());
        m_currentItem->setPos(p);
    }
    else if (property == "Width")
    {
        QSizeF s = m_currentItem->size();
        s.setWidth(value.toDouble());
        m_currentItem->setSize(s);
    }
    else if (property == "Height")
    {
        QSizeF s = m_currentItem->size();
        s.setHeight(value.toDouble());
        m_currentItem->setSize(s);
    }
    else if (property == "BackgroundColor")
    {
        QColor color(value);

        if (color.isValid())
            m_currentItem->setBackgroundColor(color);
    }
    else if (property == "ShowLabel")
    {
        m_currentItem->setLabelVisible(
            value.compare(
                "true",
                Qt::CaseInsensitive) == 0);
    }
    else if (property == "ShowBackground")
    {
        m_currentItem->setBackgroundVisible(
            value.compare(
                "true",
                Qt::CaseInsensitive) == 0);
    }

    emit propertyChanged();
}

void PropertiesDock::clearProperties(){
    m_currentItem = nullptr;
    m_propertyTree->clear();
}

