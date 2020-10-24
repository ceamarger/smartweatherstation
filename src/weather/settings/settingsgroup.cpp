#include "settingsgroup.h"

SettingsGroup::SettingsGroup(const QString& name, WeatherSettings* settings, QObject* parent)
    : QObject(parent)
    , m_name(name)
    , m_settings(settings)
{
}
