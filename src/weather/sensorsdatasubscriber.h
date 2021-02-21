#ifndef SENSORSDATASUBSCRIBER_H
#define SENSORSDATASUBSCRIBER_H

#include <QObject>
#include <QtMqtt/QMqttClient>

class SensorsDataSubscriber : public QObject {
    Q_OBJECT

public:
    enum class State { Disconnected, Connecting, Connected };
    enum class DataType { Unknown, Temperature, Humidity };
    Q_ENUM(DataType)

    explicit SensorsDataSubscriber(QObject* parent = nullptr);
    ~SensorsDataSubscriber();

    State state() const;

private slots:
    void makeDefaultSubscription() const;
    void parseReceivedMessage(const QByteArray& message, const QMqttTopicName& topic) const;

private:
    DataType topicNameToDataType(const QMqttTopicName& topic) const;
    bool connectClient() const;

    QMqttClient* m_mqttClient = nullptr;
};

namespace SensorsTopics {
static const QString SensorsGroup = "sensors";
static const QString FullSensorsGroup = SensorsGroup + "/+";
static const QString Temperature = SensorsGroup + "/temperature";
static const QString Humidity = SensorsGroup + "/humidity";
}
#endif // SENSORSDATASUBSCRIBER_H
