#pragma once

#include <QDialog>

class CanvasScene;
class QListWidget;
class QListWidgetItem;
class QAction;
class QPushButton;
class QWidget;
class CanvasTemplateManager;


class TemplateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TemplateDialog(CanvasTemplateManager* template_manager,CanvasScene* scene, QWidget* parent = nullptr);

    [[nodiscard]] QString selectedTemplate() const;

private slots:
    void switchToGridView() const;
    void switchToListView() const;
    void loadSelectedTemplate();

private:
    void loadTemplates() const;

    CanvasScene* m_scene {};
    CanvasTemplateManager* _template;
    QListWidget* m_listWidget {};

    QAction* m_gridAction {};
    QAction* m_listAction {};

    QPushButton* m_loadButton {};
    QPushButton* m_closeButton {};
};
