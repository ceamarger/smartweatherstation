#ifndef TEMPERATURECONVERTER_H
#define TEMPERATURECONVERTER_H

#include <QObject>

class TemperatureConverter : public QObject {
    Q_OBJECT

public:
    enum class TemperatureUnit { Kelvin, Celsius, Fahrenheit };
    Q_ENUM(TemperatureUnit)

    explicit TemperatureConverter(QObject* parent = nullptr);

    Q_INVOKABLE static qreal convert(qreal value, TemperatureUnit srcUnit, TemperatureUnit dstUnit);

signals:

private:
    static qreal toKelvin(qreal value, TemperatureUnit srcUnit);
    static qreal toCelsius(qreal value, TemperatureUnit srcUnit);
    static qreal toFahrenheit(qreal value, TemperatureUnit srcUnit);
};

#endif // TEMPERATURECONVERTER_H
