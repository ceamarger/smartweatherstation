#ifndef TEMPERATUREMESSAGEOPERATOR_H
#define TEMPERATUREMESSAGEOPERATOR_H

#include <QObject>

#include "../../weatherdata.h"
#include "../message.h"
#include "messageoperator.h"

class TemperatureMessageOperator : public MessageOperator {
    Q_OBJECT
public:
    explicit TemperatureMessageOperator(WeatherData* weatherData, QObject* parent = nullptr);

    void operate(const Message& message) override;

private:
    WeatherData* m_weatherData = nullptr;
};

#endif // TEMPERATUREMESSAGEOPERATOR_H
