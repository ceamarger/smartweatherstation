#include "temperatureconverter.h"

TemperatureConverter::TemperatureConverter(QObject* parent)
    : QObject(parent)
{
}

qreal TemperatureConverter::kelvinToCelsius(qreal kelvin)
{
    return kelvin - static_cast<qreal>(273.15);
}
