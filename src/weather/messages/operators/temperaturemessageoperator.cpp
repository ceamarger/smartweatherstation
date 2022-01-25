#include "temperaturemessageoperator.h"

#include <QString>
#include <QtDebug>

#include "../../indoorweatherdata.h"

TemperatureMessageOperator::TemperatureMessageOperator(WeatherData* weatherData, QObject* parent)
    : MessageOperator(parent)
    , m_weatherData(weatherData)
{
}

void TemperatureMessageOperator::operate(const Message& message)
{
    if (!isValid(message))
        return;

    auto splittedMessage = QString::fromLocal8Bit(message.message()).split(' ');

    bool ok = true;
    auto uuid = splittedMessage[0];
    auto value = splittedMessage[1].toUInt(&ok);

    m_weatherData->indoorWeatherData()->setTemperature(uuid, value);
}

bool TemperatureMessageOperator::isValid(const Message& message)
{
    if (message.type() != Message::MessageType::Temperature)
        return false;

    auto splittedMessage = QString::fromLocal8Bit(message.message()).split(' ');

    if (splittedMessage.length() == 2) {
        QRegularExpression digitRegex("\\d*");
        QRegularExpressionMatch matchDigit = digitRegex.match(splittedMessage[1]);

        return IndoorWeatherData::isValidUuid(splittedMessage[0]) && matchDigit.hasMatch();
    }

    return false;
}
