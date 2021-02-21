#include "message.h"

#include "../sensorsdatasubscriber.h"

Message::Message(MessageType type, const QByteArray& message, QObject* parent)
    : QObject(parent)
    , m_type(type)
    , m_message(message)
{
}

auto Message::mqttTopicNameToMessageType(const QMqttTopicName& topic) -> MessageType
{
    if (topic.name() == SensorsTopics::Temperature)
        return MessageType::Temperature;
    else if (topic.name() == SensorsTopics::Humidity)
        return MessageType::Humidity;

    return MessageType::Unknown;
}
