#include "weatherdata.h"

WeatherData::WeatherData(QObject *parent) : QObject(parent)
{
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
