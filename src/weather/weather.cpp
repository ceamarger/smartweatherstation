#include "weather.h"

#include <QQmlEngine>

#include "abstractweatherapiaccess.h"

const QString Weather::WeatherSettingsFileName = "WeatherSettings";

Weather::Weather(QObject* parent)
    : Weather(WeatherSettingsFileName, parent)
{
}

Weather::Weather(const QString& settingsFileName, QObject* parent)
    : QObject(parent)
    , m_settings(new WeatherSettings(settingsFileName, this))
    , m_data(new WeatherData(m_settings, this))
{
    registerQMLTypes();
}

void Weather::registerQMLTypes()
{
    qmlRegisterUncreatableType<AbstractWeatherAPIAccess>("sws.weather", 1, 0,
        "AbstractWeatherAPIAccess", "AbstractWeatherAPIAccess cannot be created in QML");

    qmlRegisterUncreatableType<WeatherData>(
        "sws.weather", 1, 0, "WeatherData", "WeatherData cannot be created in QML");
}

WeatherSettings* Weather::settings() const
{
    return m_settings;
}

WeatherData* Weather::data() const
{
    return m_data;
}
