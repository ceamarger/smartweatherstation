#include "openweathermapapisettingsgroup.h"

OpenWeatherMapAPISettingsGroup::OpenWeatherMapAPISettingsGroup(
    WeatherSettings* settings, QObject* parent)
    : SettingsGroup(OpenWeatherMapSettingsParameters::GroupName, settings, parent)
{
}

QString OpenWeatherMapAPISettingsGroup::appId() const
{
    return value(OpenWeatherMapSettingsParameters::AppId, QVariant::fromValue(QString()))
        .toString();
}

void OpenWeatherMapAPISettingsGroup::setAppId(const QString& newAppId)
{
    if (newAppId == appId())
        return;

    setValue(OpenWeatherMapSettingsParameters::AppId, newAppId);
    emit appIdChanged(newAppId);
}
