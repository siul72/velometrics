
#include "ElementsDock.h"

#include <QListWidget>

ElementsDock::ElementsDock(QWidget* parent)
    : QDockWidget("Layers", parent)
{
    m_layerList = new QListWidget(this);

    setWidget(m_layerList);
}

void ElementsDock::addLayer(
    const QString& name) const
{
    m_layerList->addItem(name);
}

void ElementsDock::removeLayer(
    const QString& name) const
{
    auto items =
        m_layerList->findItems(
            name,
            Qt::MatchExactly);

    if (!items.empty())
    {
        delete items.first();
    }
}

