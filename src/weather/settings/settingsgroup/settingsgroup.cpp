#include "settingsgroup.h"

#include "../weathersettings.h"

SettingsGroup::SettingsGroup(const QString& name, WeatherSettings* settings, QObject* parent)
    : QObject(parent)
    , m_name(name)
    , m_settings(settings)
{
}

QVariant SettingsGroup::value(const QString& key, const QVariant& defaultValue) const
{
    return value(m_name, key, defaultValue);
}

QVariant SettingsGroup::value(
    const QString& group, const QString& key, const QVariant& defaultValue) const
{
    return m_settings->value(group, key, defaultValue);
}

void SettingsGroup::setValue(const QString& key, const QVariant& value)
{
    setValue(m_name, key, value);
}

void SettingsGroup::setValue(const QString& group, const QString& key, const QVariant& value)
{
    m_settings->setValue(group, key, value);
}
