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

    connect(m_settings, &WeatherSettings::apiUsedParameterChanged, m_outdoorData.api,
        &AbstractWeatherAPIAccess::refresh);

    m_indoorData.sensorsSubscriber = new SensorsDataSubscriber(this);
}

void WeatherData::setOutdoorTemperature(quint16 outdoorTemperature)
{
    if (m_outdoorData.temperature == outdoorTemperature)
        return;

    m_outdoorData.temperature = outdoorTemperature;
    emit outdoorTemperatureChanged();
}

void WeatherData::setHumidityPercentage(quint8 humidityPercentage)
{
    if (m_outdoorData.humidityPercentage == humidityPercentage)
        return;

    m_outdoorData.humidityPercentage = humidityPercentage;
    emit humidityPercentageChanged();
}

void WeatherData::setSunriseTime(QTime sunriseTime)
{
    if (m_outdoorData.sunriseTime == sunriseTime)
        return;

    m_outdoorData.sunriseTime = sunriseTime;
    emit sunriseTimeChanged();
}

void WeatherData::setSunsetTime(QTime sunsetTime)
{
    if (m_outdoorData.sunsetTime == sunsetTime)
        return;

    m_outdoorData.sunsetTime = sunsetTime;
    emit sunsetTimeChanged();
}

void WeatherData::setIndoorTemperature(quint16 indoorTemperature)
{
    if (m_indoorData.temperature == indoorTemperature)
        return;

    m_indoorData.temperature = indoorTemperature;
    emit indoorTemperatureChanged();
}

void WeatherData::setAPI(AbstractWeatherAPIAccess* api)
{
    if (m_outdoorData.api == api)
        return;

    if (m_outdoorData.api)
        m_outdoorData.api->deleteLater();

    m_outdoorData.api = api;

    connect(m_outdoorData.api, &AbstractWeatherAPIAccess::dataUpdated, this,
        &WeatherData::parseReceivedJsonData);
}

void WeatherData::parseReceivedJsonData(QJsonDocument jsonData)
{
    using namespace WeatherDataKeys;

    setOutdoorTemperature(static_cast<quint16>(jsonData[OutdoorTemperature].toDouble() * 100));
    setHumidityPercentage(static_cast<quint8>(jsonData[Humidity].toInt()));
    setSunriseTime(QDateTime::fromSecsSinceEpoch(jsonData[Sunrise].toInt()).time());
    setSunsetTime(QDateTime::fromSecsSinceEpoch(jsonData[Sunset].toInt()).time());
}
