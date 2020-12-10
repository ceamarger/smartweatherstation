#include "weathersettingsgroup.h"

WeatherSettingsGroup::WeatherSettingsGroup(WeatherSettings* settings, QObject* parent)
    : SettingsGroup(WeatherSettingsParameters::GroupName, settings, parent)
{
}

int WeatherSettingsGroup::locationId() const
{
    return value(WeatherSettingsParameters::LocationId).toInt();
}

void WeatherSettingsGroup::setLocationId(int newLocationId)
{
    if (newLocationId == locationId())
        return;

    setValue(WeatherSettingsParameters::LocationId, newLocationId);
    emit locationIdChanged(newLocationId);
}
