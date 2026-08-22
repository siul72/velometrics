#pragma once

#include <QDockWidget>

class QTreeWidget;

class PropertiesDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit PropertiesDock(QWidget* parent = nullptr);

    void clearProperties();
    void loadProperties(
        const QString& name,
        int x,
        int y,
        int width,
        int height);

private:
    QTreeWidget* m_propertyTree;
};


