#include "abstractweatherapiaccess.h"

AbstractWeatherAPIAccess::AbstractWeatherAPIAccess(QObject *parent) : QObject(parent)
{
}

void AbstractWeatherAPIAccess::setData(QJsonDocument data)
{
    if (m_data == data)
        return;

    m_data = data;
    emit dataUpdated(m_data);
}
