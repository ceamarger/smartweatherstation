#ifndef SETTINGSGROUP_H
#define SETTINGSGROUP_H

#include <QObject>

class WeatherSettings;

class SettingsGroup : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name READ name CONSTANT)

public:
    explicit SettingsGroup(
        const QString& name, WeatherSettings* settings, QObject* parent = nullptr);
    virtual ~SettingsGroup(){};

    QString name() const { return m_name; }

signals:

protected:
    QString m_name;
    WeatherSettings* m_settings = nullptr;
};

#endif // SETTINGSGROUP_H
