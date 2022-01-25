#include "messageprocessor.h"

#include "operators/registermessageoperator.h"
#include "operators/temperaturemessageoperator.h"

MessageProcessor::MessageProcessor(WeatherData* weatherData, QObject* parent)
    : QObject(parent)
    , m_weatherData(weatherData)
{
    populateMessageOperators();
}

void MessageProcessor::processMessage(const Message& message)
{
    auto messageOperator = m_messageOperators.value(message.type(), nullptr);

    if (messageOperator)
        messageOperator->operate(message);
    else
        qDebug() << "No operator for message type :" << message.type();
}

void MessageProcessor::populateMessageOperators()
{
    using MessageType = Message::MessageType;
    m_messageOperators.insert(
        MessageType::Temperature, new TemperatureMessageOperator(m_weatherData, this));
    m_messageOperators.insert(
        MessageType::Register, new RegisterMessageOperator(m_weatherData, this));
}
