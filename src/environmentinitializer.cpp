#include "environmentinitializer.h"

#include <QQmlEngine>

#include "utils/location/locationlistmodel.h"
#include "utils/temperatureconverter.h"

EnvironmentInitializer& EnvironmentInitializer::getInstance()
{
    static EnvironmentInitializer instance;
    return instance;
}

void EnvironmentInitializer::initialize(QQmlContext* context) { initializeContext(context); }

void EnvironmentInitializer::initializeContext(QQmlContext* context)
{
    context->setContextProperty("dateTimeSettings", &m_dateTimeSettings);
    context->setContextProperty("weather", &m_weather);
    context->setContextProperty("locationFinder", &m_locationFinder);

    qmlRegisterSingletonType<TemperatureConverter>("sws.utils", 1, 0, "TemperatureConverter",
        [](QQmlEngine* engine, QJSEngine* scriptEngine) -> TemperatureConverter* {
            Q_UNUSED(engine)
            Q_UNUSED(scriptEngine)

            auto converter = new TemperatureConverter();
            return converter;
        });

    qmlRegisterUncreatableType<LocationListModel>(
        "sws.utils", 1, 0, "LocationListModel", "LocationListModel cannot be created in QML");
    qRegisterMetaType<Location*>("const Location*");
}
