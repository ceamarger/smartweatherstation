#include "temperaturesettingsgroup.h"

#include "weathersettings.h"

TemperatureSettingsGroup::TemperatureSettingsGroup(WeatherSettings* settings, QObject* parent)
    : SettingsGroup(TemperatureSettingsParameters::GroupName, settings, parent)
{
}

TemperatureSettingsGroup::TemperatureUnit TemperatureSettingsGroup::unit() const
{
    return static_cast<TemperatureSettingsGroup::TemperatureUnit>(
        m_settings
            ->value(TemperatureSettingsParameters::GroupName, TemperatureSettingsParameters::Unit)
            .toInt());
}

void TemperatureSettingsGroup::setUnit(TemperatureSettingsGroup::TemperatureUnit newUnit)
{
    if (newUnit == unit())
        return;

    m_settings->setValue(TemperatureSettingsParameters::GroupName,
        TemperatureSettingsParameters::Unit, static_cast<int>(newUnit));
    emit unitChanged(newUnit);
}
