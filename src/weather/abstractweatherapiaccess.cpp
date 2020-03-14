#include "abstractweatherapiaccess.h"

/*!
 * \brief Constructs a new AbstractWeatherAPIAccess object with the given \a parent
 * \param parent the parent of the AbstractWeatherAPIAccess object
 */
AbstractWeatherAPIAccess::AbstractWeatherAPIAccess(QObject* parent)
    : AbstractWeatherAPIAccess(nullptr, parent)
{
}

/*!
 * \brief Constructs a new AbstractWeatherAPIAccess object with the given \a parent and \a settings
 * \param settings the settings that are needed to access properly the API
 * \param parent the parent of the AbstractWeatherAPIAccess object
 */
AbstractWeatherAPIAccess::AbstractWeatherAPIAccess(WeatherSettings* settings, QObject* parent)
    : QObject(parent)
    , m_settings(settings)
{
}
