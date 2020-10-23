#ifndef TEMPERATURECONVERTER_H
#define TEMPERATURECONVERTER_H

#include <QObject>

class TemperatureConverter : public QObject {
    Q_OBJECT
public:
    explicit TemperatureConverter(QObject* parent = nullptr);

    Q_INVOKABLE static qreal kelvinToCelsius(qreal kelvin);

signals:
};

#endif // TEMPERATURECONVERTER_H
