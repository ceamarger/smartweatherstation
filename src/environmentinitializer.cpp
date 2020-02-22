#include "environmentinitializer.h"

#include <QQmlEngine>

EnvironmentInitializer& EnvironmentInitializer::getInstance()
{
    static EnvironmentInitializer instance;
    return instance;
}

void EnvironmentInitializer::initialize(QQmlContext* context)
{
    initializeContext(context);
}

void EnvironmentInitializer::initializeContext(QQmlContext* context)
{
    context->setContextProperty("dateTimeSettings", &m_dateTimeSettings);
    context->setContextProperty("weather", &m_weather);
}
