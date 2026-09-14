
#include "TemplateManager.h"

#include <qfile.h>
#include <QIcon>

TemplateManager& TemplateManager::instance()
{
    static TemplateManager instance;
    return instance;
}

QString TemplateManager::currentTemplate() const{
    return m_currentTemplate;
}

void TemplateManager::setCurrentTemplate(const QString& name){

    m_currentTemplate = name;
}

QIcon TemplateManager::icon(const QString& iconId) const {
    QString path = QString(":/templates/%1/%2.svg").arg(m_currentTemplate, iconId);

    if (QFile::exists(path))
        return QIcon(path);

    return QIcon(QString(":/templates/default/%1.svg")
        .arg(iconId));
}
