#include "temperaturesettingsgroup.h"

QList<TemperatureSettingsGroup::TemperatureUnit> const TemperatureSettingsGroup::AvailableUnits
    = { TemperatureSettingsGroup::TemperatureUnit::Kelvin,
          TemperatureSettingsGroup::TemperatureUnit::Celsius,
          TemperatureSettingsGroup::TemperatureUnit::Fahrenheit };

TemperatureSettingsGroup::TemperatureSettingsGroup(WeatherSettings* settings, QObject* parent)
    : SettingsGroup(TemperatureSettingsParameters::GroupName, settings, parent)
{
}

TemperatureSettingsGroup::TemperatureUnit TemperatureSettingsGroup::unit() const
{
    return static_cast<TemperatureSettingsGroup::TemperatureUnit>(
        value(TemperatureSettingsParameters::Unit).toInt());
}

QString TemperatureSettingsGroup::unitString() const
{
    switch (unit()) {
    case TemperatureUnit::Kelvin:
        return "K";
    case TemperatureUnit::Celsius:
        return "°C";
    case TemperatureUnit::Fahrenheit:
        return "°F";
    }
}

QString TemperatureSettingsGroup::unitFullName(TemperatureSettingsGroup::TemperatureUnit unit)
{
    switch (unit) {
    case TemperatureUnit::Kelvin:
        return "Kelvin";
    case TemperatureUnit::Celsius:
        return "Celsius";
    case TemperatureUnit::Fahrenheit:
        return "Fahrenheit";
    }
}

QStringList TemperatureSettingsGroup::availableUnitsStrings()
{
    QStringList availableUnits;
    for (auto availableUnit : AvailableUnits)
        availableUnits.append(unitFullName(availableUnit));

    return availableUnits;
}

TemperatureSettingsGroup::TemperatureUnit TemperatureSettingsGroup::availableUnitAtIndex(int index)
{
    Q_ASSERT_X(index >= 0 && index < AvailableUnits.length(), Q_FUNC_INFO, "index out of range");
    return AvailableUnits[index];
}

int TemperatureSettingsGroup::availableUnitIndex(TemperatureSettingsGroup::TemperatureUnit unit)
{
    auto unitIt = std::find_if(AvailableUnits.begin(), AvailableUnits.end(),
        [unit](TemperatureUnit availableUnit) { return availableUnit == unit; });

    return unitIt != AvailableUnits.end() ? std::distance(AvailableUnits.begin(), unitIt) : -1;
}

void TemperatureSettingsGroup::setUnit(TemperatureSettingsGroup::TemperatureUnit newUnit)
{
    if (newUnit == unit())
        return;

    setValue(TemperatureSettingsParameters::Unit, static_cast<int>(newUnit));
    emit unitChanged(newUnit);
}
