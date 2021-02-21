#include "sensorsdatasubscriber.h"

#include <QMetaEnum>
#include <QTimer>

SensorsDataSubscriber::SensorsDataSubscriber(QObject* parent)
    : QObject(parent)
    , m_mqttClient(new QMqttClient(this))
{
    connectClient();
}

SensorsDataSubscriber::~SensorsDataSubscriber() { m_mqttClient->disconnectFromHost(); }

auto SensorsDataSubscriber::state() const -> State
{
    if (m_mqttClient) {
        switch (m_mqttClient->state()) {
        case QMqttClient::ClientState::Disconnected:
            return State::Disconnected;
        case QMqttClient::ClientState::Connecting:
            return State::Connecting;
        case QMqttClient::ClientState::Connected:
            return State::Connected;
        }
    }

    return State::Disconnected;
}

void SensorsDataSubscriber::makeDefaultSubscription() const
{
    using namespace SensorsTopics;
    if (!m_mqttClient->subscribe(FullSensorsGroup)) {
        qDebug() << "Could not subscribe. Is there a valid connection?";
    }
}

void SensorsDataSubscriber::parseReceivedMessage(
    const QByteArray& message, const QMqttTopicName& topic) const
{
    auto type = topicNameToDataType(topic);
    switch (type) {
    case DataType::Temperature:
        qDebug() << "Temperature:" << message;
        break;
    case DataType::Unknown:
        qDebug() << "Unknown topic:" << topic.name();
        break;
    default:
        qDebug() << "Not supported:" << type;
        break;
    }
}

auto SensorsDataSubscriber::topicNameToDataType(const QMqttTopicName& topic) const -> DataType
{
    if (topic.name() == SensorsTopics::Temperature)
        return DataType::Temperature;
    else if (topic.name() == SensorsTopics::Humidity)
        return DataType::Humidity;

    return DataType::Unknown;
}

bool SensorsDataSubscriber::connectClient() const
{
    if (!m_mqttClient)
        return false;

    connect(m_mqttClient, &QMqttClient::errorChanged, this,
        [](QMqttClient::ClientError error) { qDebug() << "MQTT client error :" << error; });

    connect(m_mqttClient, &QMqttClient::stateChanged, this,
        [](QMqttClient::ClientState state) { qDebug() << "MQTT client state :" << state; });

    connect(m_mqttClient, &QMqttClient::connected, this,
        &SensorsDataSubscriber::makeDefaultSubscription);

    connect(m_mqttClient, &QMqttClient::messageReceived, this,
        &SensorsDataSubscriber::parseReceivedMessage);

    connect(m_mqttClient, &QMqttClient::pingResponseReceived, this, []() {
        qDebug() << QDateTime::currentDateTime().toString() << QLatin1String("PingResponse");
    });

    m_mqttClient->setHostname("127.0.0.1");
    m_mqttClient->setPort(1883);
    m_mqttClient->connectToHost();

    return true;
}
