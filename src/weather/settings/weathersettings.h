#ifndef WEATHERSETTINGS_H
#define WEATHERSETTINGS_H

#include <QMap>
#include <QObject>
#include <QSettings>

#include <memory>

#include "settingsgroup.h"

class TemperatureSettingsGroup;

/*!
 * \class WeatherSettings
 * \brief A class that can be used to store settings in a file.
 *
 * WeatherSettings class can be used to store settings in a file.
 * The file is formated as an INI file.
 */
class WeatherSettings : public QObject {
    Q_OBJECT

    Q_PROPERTY(SettingsGroup* temperatureSettings READ temperatureSettings CONSTANT)

public:
    explicit WeatherSettings(const QString& filename, QObject* parent = nullptr);

    QVariant value(
        const QString& group, const QString& key, const QVariant& defaultValue = QVariant()) const;
    void setValue(const QString& group, const QString& key, const QVariant& value);

    TemperatureSettingsGroup* temperatureSettings();

signals:

private:
    // NOTE (camar) : Maybe move group() and addGroup() to public to allow custom settings
    SettingsGroup* group(const QString& name) const;
    void addGroup(SettingsGroup* group);

    void createDefaultGroups();

    QSettings* m_settings = nullptr;
    QList<SettingsGroup*> m_settingsGroups;
};

#endif // WEATHERSETTINGS_H
