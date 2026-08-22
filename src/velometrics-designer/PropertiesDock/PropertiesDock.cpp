
#include "PropertiesDock.h"
#include <QTreeWidgetItem>

PropertiesDock::PropertiesDock(QWidget* parent)
    : QDockWidget("Properties", parent)
{
    m_propertyTree = new QTreeWidget(this);

    m_propertyTree->setColumnCount(2);

    m_propertyTree->setHeaderLabels(
    {
        "Property",
        "Value"
    });

    setWidget(m_propertyTree);
}


