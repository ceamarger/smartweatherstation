#include "abstractweatherapiaccess.h"

AbstractWeatherAPIAccess::AbstractWeatherAPIAccess(QObject* parent)
    : AbstractWeatherAPIAccess(nullptr, parent)
{
}

AbstractWeatherAPIAccess::AbstractWeatherAPIAccess(WeatherSettings* settings, QObject* parent)
    : QObject(parent)
    , m_settings(settings)
{
}
