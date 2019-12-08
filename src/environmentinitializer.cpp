#include "environmentinitializer.h"

EnvironmentInitializer &EnvironmentInitializer::getInstance()
{
    static EnvironmentInitializer instance;
    return instance;
}

void EnvironmentInitializer::initializeContext(QQmlContext* context)
{
    context->setContextProperty("dateTimeSettings", dateTimeSettings());
    context->setContextProperty("weatherData", weatherData());
}
