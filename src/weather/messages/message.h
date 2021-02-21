#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QtMqtt/qmqtttopicname.h>

class Message : public QObject {
    Q_OBJECT
public:
    enum class MessageType { Unknown, Temperature, Humidity };
    Q_ENUM(MessageType)

    explicit Message(MessageType type, const QByteArray& message, QObject* parent = nullptr);

    MessageType type() const { return m_type; }
    QByteArray message() const { return m_message; }

    static MessageType mqttTopicNameToMessageType(const QMqttTopicName& topic);

private:
    MessageType m_type;
    QByteArray m_message;
};

#endif // MESSAGE_H
