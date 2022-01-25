#include "weather.h"

#include <QQmlEngine>

#include "abstractweatherapiaccess.h"
#include "settings/settingsgroup/temperaturesettingsgroup.h"

const QString Weather::WeatherSettingsFileName = "WeatherSettings";

/*!
 * \brief Constructs a Weather object with the given \a parent and default settings file
 * \param parent parent of the object
 */
Weather::Weather(QObject* parent)
    : Weather(WeatherSettingsFileName, parent)
{
    connect(&m_sensorsSubscriber, &SensorsDataSubscriber::sensorMessageReceived,
        &m_messageProcessor, &MessageProcessor::processMessage);
}

/*!
 * \brief Constructs a Weather object with the given \a parent and settings file with the given \a
 * settingsFileName
 *
 * \param settingsFileName name of the settings file
 * \param parent parent of the object
 */
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
    qmlRegisterUncreatableType<WeatherSettings>(
        "sws.weather", 1, 0, "WeatherSettings", "WeatherSettings cannot be created in QML");
    qmlRegisterUncreatableType<SettingsGroup>(
        "sws.weather", 1, 0, "SettingsGroup", "SettingsGroup cannot be created in QML");
    qmlRegisterUncreatableType<TemperatureSettingsGroup>("sws.weather", 1, 0,
        "TemperatureSettingsGroup", "TemperatureSettingsGroup cannot be created in QML");
}
