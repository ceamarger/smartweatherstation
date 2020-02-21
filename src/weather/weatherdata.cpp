#include "weatherdata.h"

#include "openweathermapaccess.h"
#include "weatherdatajsonkeys.h"

#include <QtDebug>

WeatherData::WeatherData(WeatherSettings* settings, QObject* parent)
    : QObject(parent)
    , m_settings(settings)
{
    // TODO (camar) : manage api change
    setWeatherAPIAccess(new OpenWeatherMapAccess(m_settings, this));
}

void WeatherData::setOutdoorTemperature(quint16 outdoorTemperature)
{
    if (m_outdoorTemperature == outdoorTemperature)
        return;

    m_outdoorTemperature = outdoorTemperature;
    emit outdoorTemperatureChanged();
}

void WeatherData::setHumidityPercentage(quint8 humidityPercentage)
{
    if (m_humidityPercentage == humidityPercentage)
        return;

    m_humidityPercentage = humidityPercentage;
    emit humidityPercentageChanged();
}

void WeatherData::setSunriseTime(QTime sunriseTime)
{
    if (m_sunriseTime == sunriseTime)
        return;

    m_sunriseTime = sunriseTime;
    emit sunriseTimeChanged();
}

void WeatherData::setSunsetTime(QTime sunsetTime)
{
    if (m_sunsetTime == sunsetTime)
        return;

    m_sunsetTime = sunsetTime;
    emit sunsetTimeChanged();
}

void WeatherData::setWeatherAPIAccess(AbstractWeatherAPIAccess* weatherAPIAccess)
{
    if (m_api == weatherAPIAccess)
        return;

    if (m_api)
        m_api->deleteLater();

    m_api = weatherAPIAccess;

    connect(
        m_api, &AbstractWeatherAPIAccess::dataUpdated, this, &WeatherData::parseReceivedJsonData);
}

void WeatherData::parseReceivedJsonData(QJsonDocument jsonData)
{
    using namespace WeatherDataKeys;

    setOutdoorTemperature(static_cast<quint16>(jsonData[OutdoorTemperature].toDouble() * 100));
    setHumidityPercentage(static_cast<quint8>(jsonData[Humidity].toInt()));
    setSunriseTime(QDateTime::fromSecsSinceEpoch(jsonData[Sunrise].toInt()).time());
    setSunsetTime(QDateTime::fromSecsSinceEpoch(jsonData[Sunset].toInt()).time());
}
