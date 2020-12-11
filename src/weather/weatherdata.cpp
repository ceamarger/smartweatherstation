#include "weatherdata.h"

#include "openweathermapaccess.h"
#include "weatherdatajsonkeys.h"

#include <QtDebug>

/*!
 * \brief Constructs a WeatherData object with the given \a parent and \a settings
 * \param settings the settings needed by the object
 * \param parent the parent of the object
 */
WeatherData::WeatherData(WeatherSettings* settings, QObject* parent)
    : QObject(parent)
    , m_settings(settings)
{
    // TODO (camar) : manage api change
    setAPI(new OpenWeatherMapAccess(m_settings, this));

    connect(m_settings, &WeatherSettings::apiUsedParameterChanged, m_api,
        &AbstractWeatherAPIAccess::refresh);
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

void WeatherData::setIndoorTemperature(quint16 indoorTemperature)
{
    if (m_indoorTemperature == indoorTemperature)
        return;

    m_indoorTemperature = indoorTemperature;
    emit indoorTemperatureChanged();
}

void WeatherData::setAPI(AbstractWeatherAPIAccess* api)
{
    if (m_api == api)
        return;

    if (m_api)
        m_api->deleteLater();

    m_api = api;

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
