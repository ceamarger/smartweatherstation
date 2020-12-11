#include "generalweathersettingsgroup.h"

GeneralWeatherSettingsGroup::GeneralWeatherSettingsGroup(WeatherSettings* settings, QObject* parent)
    : SettingsGroup(GeneralWeatherSettingsParameters::GroupName, settings, parent)
{
}

int GeneralWeatherSettingsGroup::locationId() const
{
    return value(GeneralWeatherSettingsParameters::LocationId, -1).toInt();
}

void GeneralWeatherSettingsGroup::setLocationId(int newLocationId)
{
    if (newLocationId == locationId())
        return;

    setValue(GeneralWeatherSettingsParameters::LocationId, newLocationId);
    emit locationIdChanged(newLocationId);
}
