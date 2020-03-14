#include "weathersettings.h"

/*!
 * \brief Constructs a new weather settings object with the given parent and the given \a filename
 * file
 *
 * \param filename the file that stores the settings
 * \param parent parent of the weatherSettings object
 */
WeatherSettings::WeatherSettings(const QString& filename, QObject* parent)
    : QObject(parent)
    , m_settings(new QSettings(filename, QSettings::IniFormat, this))
{
}

/*!
 * \brief Get the value matching the given \a group and \a key
 * \param group the group containing the wanted setting
 * \param key the key corresponding to the wanted setting
 * \param defaultValue the default value to use if the wanted setting is not found
 * \return The value that matches \a group and \a key, or \a defaultValue if not found
 *
 * \sa setValue()
 */
QVariant WeatherSettings::value(
    const QString& group, const QString& key, const QVariant& defaultValue) const
{
    m_settings->beginGroup(group);
    auto result = m_settings->value(key, defaultValue);
    m_settings->endGroup();

    return result;
}

/*!
 * \brief Set the \a value fir the setting matching the given \a group and
 * \a key
 *
 * \param group the group containing the wanted setting
 * \param key the key corresponding to the wanted setting
 * \param value the new value to give to the setting
 *
 * \sa value()
 */
void WeatherSettings::setValue(const QString& group, const QString& key, const QVariant& value)
{
    m_settings->beginGroup(group);
    m_settings->setValue(key, value);
    m_settings->endGroup();
}
