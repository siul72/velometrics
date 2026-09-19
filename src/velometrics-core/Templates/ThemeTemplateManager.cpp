#include "ThemeTemplateManager.h"

#include <qfile.h>
#include <QIcon>

ThemeTemplateManager& ThemeTemplateManager::instance()
{
    static ThemeTemplateManager instance;
    return instance;
}

QString ThemeTemplateManager::currentTemplate() const{
    return m_currentTemplate;
}

void ThemeTemplateManager::setCurrentTemplate(const QString& name){

    m_currentTemplate = name;
}

QIcon ThemeTemplateManager::icon(const QString& iconId) const {
    QString path = QString(":/templates/%1/%2.svg").arg(m_currentTemplate, iconId);

    if (QFile::exists(path))
        return QIcon(path);

    return QIcon(QString(":/templates/default/%1.svg")
        .arg(iconId));
}
