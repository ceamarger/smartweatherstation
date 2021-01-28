#ifndef OPENWEATHERMAPAPISETTINGSGROUP_H
#define OPENWEATHERMAPAPISETTINGSGROUP_H

#include "settingsgroup.h"
#include <QObject>

class OpenWeatherMapAPISettingsGroup : public SettingsGroup {
    Q_OBJECT

    Q_PROPERTY(QString appId READ appId WRITE setAppId NOTIFY appIdChanged)

public:
    explicit OpenWeatherMapAPISettingsGroup(WeatherSettings* settings, QObject* parent = nullptr);

    QString appId() const;

    void setAppId(const QString& newAppId);

signals:
    void appIdChanged(QString appId);
};

namespace OpenWeatherMapSettingsParameters {

static const QString GroupName = "OWMSettings";
static const QString AppId = "appId";
}

#endif // OPENWEATHERMAPAPISETTINGSGROUP_H
