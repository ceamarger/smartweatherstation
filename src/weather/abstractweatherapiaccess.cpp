#include "abstractweatherapiaccess.h"

AbstractWeatherAPIAccess::AbstractWeatherAPIAccess(QObject *parent) : QObject(parent)
{
}

void AbstractWeatherAPIAccess::setSettings(QSettings *settings)
{
    if (m_settings == settings)
        return;

    if (m_settings)
        m_settings->deleteLater();

    m_settings = settings;
}

void AbstractWeatherAPIAccess::setData(QJsonDocument data)
{
    if (m_data == data)
        return;

    m_data = data;
    emit dataUpdated(m_data);
}
