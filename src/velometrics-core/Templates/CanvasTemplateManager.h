#pragma once

#include <QString>
#include <QStringList>

#include "../../velometrics-designer/Canvas/CanvasScene.h"

class CanvasTemplateManager: public QObject {

    Q_OBJECT

public:
    static CanvasTemplateManager& instance(QObject* parent = nullptr);
    explicit CanvasTemplateManager(QObject* parent = nullptr);

    CanvasTemplateManager(const CanvasTemplateManager&) = delete;
    CanvasTemplateManager& operator=(const CanvasTemplateManager&) = delete;

    QString templateDirectory();
    QString saveTemplate(CanvasScene* scene, const QString& name);
    [[nodiscard]] bool loadTemplate(CanvasScene* scene, const QString& name) const;
    [[nodiscard]] QStringList availableTemplates();
    void invalidateCache();

private:
    QString m_template_directory;
    QStringList m_templates{};
};
