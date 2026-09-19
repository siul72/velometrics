#include "CanvasTemplateManager.h"

#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>

#include "../../velometrics-designer/Elements/TelemetryWidgetItem.h"

CanvasTemplateManager& CanvasTemplateManager::instance(QObject* parent) {

    static CanvasTemplateManager instance(parent);
    return instance;

}

CanvasTemplateManager::CanvasTemplateManager(QObject* parent): QObject(parent) {

    const QDir dir(templateDirectory());

    for (const QStringList files =dir.entryList({"*.bin"},QDir::Files,QDir::Time); const QString& file : files){
        m_templates.append(QFileInfo(file).completeBaseName());
    }
}

QString CanvasTemplateManager::templateDirectory() {
    if (m_template_directory != nullptr) {
        return m_template_directory;
    }
    const QString appDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    const QDir dir(appDataDir);

    if (!dir.exists()){
        auto ret = dir.mkpath(".");
    }

    auto ret = dir.mkpath("templates");
    m_template_directory = dir.filePath("templates");
    return m_template_directory;
}


QString CanvasTemplateManager::saveTemplate(CanvasScene* scene, const QString& name) const
{

    QString templateName = name;
    if (templateName.isEmpty()){
        templateName =QString("template_%1")
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
    }

    QFile file(QDir(m_template_directory).filePath(templateName + ".bin"));
    if (!file.open(QIODevice::WriteOnly))
        return {};

    QDataStream stream(&file);
    stream << static_cast<quint32>(1);
    qDebug() << "1 File position save:" << file.pos();
    stream << scene->sceneRect().size();
    qDebug() << "2 File position save:" << file.pos();
    //stream << scene->m_config.canvasBackgroundColor;
    //qDebug() << "3 File position save:" << file.pos();
    QVector<TelemetryWidgetItem*> widgets;

    for (auto* item : scene->items()){
        if (auto* widget = dynamic_cast<TelemetryWidgetItem*>(item)){
            widgets.append(widget);
        }
    }

    stream << widgets.size();
    qDebug() << "4 File position save:" << file.pos();
    for (const auto* widget : widgets){
        widget->serialize(stream);
    }

    auto ret = scene->renderFrame(QSize(320, 180),scene->m_config.canvasBackgroundColor)
    .save(QDir(m_template_directory).filePath(templateName + ".png"));

    return templateName;
}

bool CanvasTemplateManager::loadTemplate(CanvasScene* scene, const QString& name) const{
    QFile file(QDir(m_template_directory).filePath(name + ".bin"));

    if (!file.open(QIODevice::ReadOnly))
        return false;
    QDataStream stream(&file);
    quint32 version;
    QSizeF canvasSize;
    QColor canvasBackgroundColor;
    int widgetCount;
    stream >> version;
    qDebug() << "1 File position load:" << file.pos();
    stream >> canvasSize;
    qDebug() << "2 File position load:" << file.pos();
    //stream >> canvasBackgroundColor;
    //qDebug() << "3 File position load:" << file.pos();
    stream >> widgetCount;
    qDebug() << "4 File position load:" << file.pos();
    scene->clear();
    scene->setSceneRect(QRectF(QPointF(0, 0), canvasSize));
    scene->m_config.canvasBackgroundColor = canvasBackgroundColor;

    for (int i = 0; i < widgetCount; ++i){
        qint32 elementType;
        stream >> elementType;
        const auto def = elementDefinitions.value(static_cast<ElementType>(elementType));
        auto* widget = new TelemetryWidgetItem(def);
        widget->deserialize(stream);
        scene->addItem(widget);
    }
    //scene->setHelpersVisible(true);
    return true;
}

QStringList CanvasTemplateManager::availableTemplates(){
    if (!m_templates.isEmpty()){
        return m_templates;
    }
    const QDir dir(m_template_directory);
    for (const QStringList files = dir.entryList({"*.bin"},QDir::Files,QDir::Time); const QString& file : files) {
        m_templates.append(QFileInfo(file).completeBaseName());
    }
    return m_templates;
}

void CanvasTemplateManager::invalidateCache() {
    m_templates.clear();
}