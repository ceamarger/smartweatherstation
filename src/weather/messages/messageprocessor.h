#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include <QObject>

#include "../weatherdata.h"
#include "message.h"
#include "operators/messageoperator.h"

class MessageProcessor : public QObject {
    Q_OBJECT

public:
    explicit MessageProcessor(WeatherData* weatherData, QObject* parent = nullptr);

public slots:
    void processMessage(const Message& message);

private:
    void populateMessageOperators();

    WeatherData* m_weatherData;
    QMap<Message::MessageType, MessageOperator*> m_messageOperators;
};

#endif // MESSAGEPROCESSOR_H
