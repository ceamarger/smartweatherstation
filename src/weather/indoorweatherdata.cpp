#include "indoorweatherdata.h"

#include <QRegularExpression>
#include <QtDebug>

IndoorWeatherData::IndoorWeatherData(QObject* parent)
    : QObject(parent)
{
}

Room* IndoorWeatherData::mainRoom() { return roomByUuid(m_mainRoomUuid); }

Room* IndoorWeatherData::roomByUuid(const QString& uuid)
{
    if (uuid.isEmpty())
        return nullptr;

    auto rooms = m_rooms.list();

    auto roomItr = std::find_if(
        rooms.begin(), rooms.end(), [&uuid](Room* room) { return room->uuid() == uuid; });

    return roomItr != rooms.end() ? *roomItr : nullptr;
}

void IndoorWeatherData::appendRoom(Room* const& room)
{
    m_rooms.append(room);

    // If this is the only room, we set it as the main room by default
    if (m_rooms.rowCount() == 1)
        setMainRoomUuid(room->uuid());
}

void IndoorWeatherData::registerRoom(const QString& uuid, const QString& name)
{
    appendRoom(new Room(uuid, name, this));
}

void IndoorWeatherData::setMainRoomUuid(const QString& mainRoomUuid)
{
    if (m_mainRoomUuid == mainRoomUuid)
        return;

    m_mainRoomUuid = mainRoomUuid;
    emit mainRoomChanged();
}

void IndoorWeatherData::setTemperature(const QString& uuid, quint16 temperature)
{
    auto room = roomByUuid(uuid);
    if (!room) {
        qDebug() << "No room for uuid :" << uuid;
        return;
    }

    room->setTemperature(temperature);
}

bool IndoorWeatherData::isValidUuid(const QString& uuid)
{
    QRegularExpression re("[a-f0-9]{8}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{12}");
    QRegularExpressionMatch match = re.match(uuid);

    return match.hasMatch();
}
