#ifndef SENSORSDATASUBSCRIBER_H
#define SENSORSDATASUBSCRIBER_H

#include <QObject>
#include <QtMqtt/QMqttClient>

#include "messages/message.h"

class SensorsDataSubscriber : public QObject {
    Q_OBJECT

public:
    enum class State { Disconnected, Connecting, Connected };
    Q_ENUM(State)

    explicit SensorsDataSubscriber(QObject* parent = nullptr);
    ~SensorsDataSubscriber();

    State state() const;

signals:
    void sensorMessageReceived(const Message& message);

private slots:
    void makeDefaultSubscription() const;
    void parseReceivedMessage(const QByteArray& message, const QMqttTopicName& topic);

private:
    bool connectClient() const;

    QMqttClient* m_mqttClient = nullptr;
};

namespace SensorsTopics {
static const QString SensorsGroup = "sensors";
static const QString FullSensorsGroup = SensorsGroup + "/+";
static const QString TemperatureCommand = SensorsGroup + "/temperature";
static const QString HumidityCommand = SensorsGroup + "/humidity";

static const QString RegisterCommand = SensorsGroup + "/register";
}
#endif // SENSORSDATASUBSCRIBER_H
