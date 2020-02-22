#include "weathersettings.h"

WeatherSettings::WeatherSettings(const QString& filename, QObject* parent)
    : QObject(parent)
    , m_settings(new QSettings(filename, QSettings::IniFormat, this))
{
}

QVariant WeatherSettings::value(
    const QString& group, const QString& key, const QVariant& defaultValue) const
{
    m_settings->beginGroup(group);
    auto result = m_settings->value(key, defaultValue);
    m_settings->endGroup();

    return result;
}

void WeatherSettings::setValue(const QString& group, const QString& key, const QVariant& value)
{
    m_settings->beginGroup(group);
    m_settings->setValue(key, value);
    m_settings->endGroup();
}
