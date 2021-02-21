#include "temperaturemessageoperator.h"

#include <QString>
#include <QtDebug>

TemperatureMessageOperator::TemperatureMessageOperator(WeatherData* weatherData, QObject* parent)
    : MessageOperator(parent)
    , m_weatherData(weatherData)
{
}

void TemperatureMessageOperator::operate(const Message& message)
{
    bool isValid = true;
    auto value = QString::fromLocal8Bit(message.message()).toInt(&isValid);
    if (isValid)
        m_weatherData->setIndoorTemperature(value);
}
