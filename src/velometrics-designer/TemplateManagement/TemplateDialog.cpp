#include "TemplateDialog.h"
#include "../Canvas/CanvasScene.h"

#include <QAction>
#include <QDir>
#include <QIcon>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QToolBar>
#include <QVBoxLayout>
#include <QStyle>

#include "../../velometrics-core/Templates/CanvasTemplateManager.h"

TemplateDialog::TemplateDialog(CanvasTemplateManager* template_manager, CanvasScene* scene,QWidget* parent)
    : QDialog(parent),
      m_scene(scene){
    setWindowTitle(tr("Templates"));
    resize(1000, 700);

    _template = template_manager;
    auto* mainLayout = new QVBoxLayout(this);
    auto* toolbar = new QToolBar(this);

    mainLayout->addWidget(toolbar);
    m_gridAction = toolbar->addAction(
        style()->standardIcon(QStyle::SP_FileDialogContentsView),
        tr("Grid"));

    m_listAction = toolbar->addAction(
        style()->standardIcon(QStyle::SP_FileDialogDetailedView),
        tr("List"));

    m_gridAction->setCheckable(true);
    m_listAction->setCheckable(true);
    m_gridAction->setChecked(true);
    m_listWidget = new QListWidget(this);

    m_listWidget->setSelectionMode(
        QAbstractItemView::SingleSelection);

    m_listWidget->setViewMode(
        QListView::IconMode);

    m_listWidget->setResizeMode(
        QListView::Adjust);

    m_listWidget->setMovement(
        QListView::Static);

    m_listWidget->setIconSize(
        QSize(320, 180));

    m_listWidget->setGridSize(
        QSize(340, 240));

    mainLayout->addWidget(m_listWidget);

    auto* buttonLayout = new QHBoxLayout();

    buttonLayout->addStretch();

    m_loadButton = new QPushButton(
        tr("Load"),
        this);

    m_closeButton = new QPushButton(
        tr("Close"),
        this);

    buttonLayout->addWidget(m_loadButton);
    buttonLayout->addWidget(m_closeButton);

    mainLayout->addLayout(buttonLayout);

    connect(
        m_gridAction,
        &QAction::triggered,
        this,
        &TemplateDialog::switchToGridView);

    connect(
        m_listAction,
        &QAction::triggered,
        this,
        &TemplateDialog::switchToListView);

    connect(
        m_loadButton,
        &QPushButton::clicked,
        this,
        &TemplateDialog::loadSelectedTemplate);

    connect(
        m_closeButton,
        &QPushButton::clicked,
        this,
        &QDialog::reject);


    connect(
        m_listWidget,
        &QListWidget::itemDoubleClicked,
    this,
    &TemplateDialog::loadSelectedTemplate);

    loadTemplates();
}

void TemplateDialog::loadTemplates() const
{
    m_listWidget->clear();
    const QString templateDir = _template->templateDirectory();
    for (const QString& templateName : CanvasTemplateManager::instance().availableTemplates()) {
        auto* item = new QListWidgetItem();
        item->setText(templateName);
        item->setIcon(QIcon(QDir(templateDir).filePath(templateName + ".png")));
        m_listWidget->addItem(item);
    }

    if (m_listWidget->count() > 0){
        m_listWidget->setCurrentRow(0);
    }
}

void TemplateDialog::switchToGridView() const
{
    m_gridAction->setChecked(true);
    m_listAction->setChecked(false);

    m_listWidget->setViewMode(
        QListView::IconMode);

    m_listWidget->setIconSize(
        QSize(320, 180));

    m_listWidget->setGridSize(
        QSize(340, 240));
}

void TemplateDialog::switchToListView() const
{
    m_listAction->setChecked(true);
    m_gridAction->setChecked(false);

    m_listWidget->setViewMode(
        QListView::ListMode);

    m_listWidget->setIconSize(
        QSize(64, 64));
}


void TemplateDialog::loadSelectedTemplate(){
    const auto* item = m_listWidget->currentItem();
    if (!item)
        return;
    auto ret = _template->loadTemplate(m_scene, item->text());
    accept();
}



QString TemplateDialog::selectedTemplate() const
{
    const auto* item = m_listWidget->currentItem();
    if (!item){
        return {};
    }
    return item->text();
}
