#pragma once

#include <QDockWidget>

#include "../common/ElementType.h"

class QTreeWidget;
class QTreeWidgetItem;

class ElementsDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit ElementsDock(QWidget* parent = nullptr);

    signals:
        void elementRequested(ElementType element);


private slots:
    void onItemDoubleClicked(
        const QTreeWidgetItem* item,
        int column);

private:
    void buildTree() const;

    QTreeWidget* m_tree;
};