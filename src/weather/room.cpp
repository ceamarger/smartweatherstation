#include "room.h"

Room::Room(QObject* parent)
    : Room(QString(), QString(), parent)
{
}

Room::Room(const QString& uuid, const QString& name, QObject* parent)
    : QObject(parent)
    , m_uuid(uuid)
    , m_name(name)
{
}

void Room::setTemperature(quint16 temperature)
{
    if (hasTemperature() && m_temperature == temperature)
        return;

    m_temperature = temperature;
    emit temperatureChanged();
}
