#pragma once
#include <QObject>
#include <QString>


class ThemeTemplateManager : public QObject
{
    Q_OBJECT

public:
    static ThemeTemplateManager& instance();

    [[nodiscard]] QString currentTemplate() const;
    void setCurrentTemplate(const QString& name);

    [[nodiscard]] QIcon icon(const QString& iconId) const;

private:
    QString m_currentTemplate = "default";
};

