#ifndef REGISTERMESSAGEOPERATOR_H
#define REGISTERMESSAGEOPERATOR_H

#include <QObject>

#include "../../weatherdata.h"
#include "../message.h"
#include "messageoperator.h"

class RegisterMessageOperator : public MessageOperator {
    Q_OBJECT
public:
    explicit RegisterMessageOperator(WeatherData* weatherData, QObject* parent = nullptr);

    void operate(const Message& message) override;
    bool isValid(const Message& message) override;

private:
    WeatherData* m_weatherData = nullptr;
};

#endif // REGISTERMESSAGEOPERATOR_H
