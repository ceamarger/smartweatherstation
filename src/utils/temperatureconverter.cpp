#include "temperatureconverter.h"

TemperatureConverter::TemperatureConverter(QObject* parent)
    : QObject(parent)
{
}

qreal TemperatureConverter::convert(qreal value, TemperatureConverter::TemperatureUnit srcUnit,
    TemperatureConverter::TemperatureUnit dstUnit)
{
    switch (dstUnit) {
    case TemperatureUnit::Kelvin:
        return toKelvin(value, srcUnit);
    case TemperatureUnit::Celsius:
        return toCelsius(value, srcUnit);
    case TemperatureUnit::Fahrenheit:
        return toFahrenheit(value, srcUnit);
    default:
        return .0;
    }
}

qreal TemperatureConverter::toKelvin(qreal value, TemperatureConverter::TemperatureUnit srcUnit)
{
    switch (srcUnit) {
    case TemperatureUnit::Kelvin:
        return value;
    case TemperatureUnit::Celsius:
        return value + 273.15;
    case TemperatureUnit::Fahrenheit:
        return (value + 459.67) * 5 / 9;
    default:
        return .0;
    }
}

qreal TemperatureConverter::toCelsius(qreal value, TemperatureConverter::TemperatureUnit srcUnit)
{
    switch (srcUnit) {
    case TemperatureUnit::Kelvin:
        return value - 273.15;
    case TemperatureUnit::Celsius:
        return value;
    case TemperatureUnit::Fahrenheit:
        return (value - 32) * 5 / 9;
    default:
        return .0;
    }
}

qreal TemperatureConverter::toFahrenheit(qreal value, TemperatureConverter::TemperatureUnit srcUnit)
{
    switch (srcUnit) {
    case TemperatureUnit::Kelvin:
        return (value - 273.15) * 9 / 5 + 32;
    case TemperatureUnit::Celsius:
        return (value * 9 / 5) + 32;
    case TemperatureUnit::Fahrenheit:
        return value;
    default:
        return .0;
    }
}
