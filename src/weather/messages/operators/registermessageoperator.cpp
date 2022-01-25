#include "registermessageoperator.h"

RegisterMessageOperator::RegisterMessageOperator(WeatherData* weatherData, QObject* parent)
    : MessageOperator(parent)
    , m_weatherData(weatherData)
{
}

void RegisterMessageOperator::operate(const Message& message)
{
    if (!isValid(message))
        return;

    emit m_weatherData->indoorWeatherData()->newRoomReceived(QString::fromLocal8Bit(message.message()));
}

bool RegisterMessageOperator::isValid(const Message& message)
{
    if (message.type() != Message::MessageType::Register)
        return false;

    return IndoorWeatherData::isValidUuid(QString::fromLocal8Bit(message.message()));
}
