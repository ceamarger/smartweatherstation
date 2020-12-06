#include "weathersettingsgroup.h"

WeatherSettingsGroup::WeatherSettingsGroup(WeatherSettings* settings, QObject* parent)
    : SettingsGroup(WeatherSettingsParameters::GroupName, settings, parent)
{
}
