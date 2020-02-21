#include "environmentinitializer.h"

#include <QQmlEngine>

EnvironmentInitializer &EnvironmentInitializer::getInstance()
{
    static EnvironmentInitializer instance;
    return instance;
}

EnvironmentInitializer::~EnvironmentInitializer()
{
    m_weatherData->deleteLater();
    m_weatherSettings->deleteLater();
}

void EnvironmentInitializer::initialize(QQmlContext* context)
{
    initializeEnvironment();
    registerQMLTypes();
    initializeContext(context);
}

void EnvironmentInitializer::initializeEnvironment()
{
    // TODO (camar) : check weatherSettings parent
    m_weatherSettings = new WeatherSettings("WeatherSettings");
    m_weatherData = new WeatherData(m_weatherSettings);
}

void EnvironmentInitializer::initializeContext(QQmlContext* context)
{
    context->setContextProperty("dateTimeSettings", &m_dateTimeSettings);
    context->setContextProperty("weatherData", m_weatherData);
}

void EnvironmentInitializer::registerQMLTypes()
{

    qmlRegisterUncreatableType<AbstractWeatherAPIAccess>("sws.weather",
                                                         1, 0,
                                                         "AbstractWeatherAPIAccess",
                                                         "AbstractWeatherAPIAccess cannot be created in QML");
}
