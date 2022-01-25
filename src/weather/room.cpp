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
    connect(this, &Room::temperatureChanged, this, &Room::dataChanged);
}

void Room::setTemperature(quint16 temperature)
{
    if (hasTemperature() && m_temperature == temperature)
        return;

    m_temperature = temperature;
    emit temperatureChanged();
}

RoomListModel::RoomListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> RoomListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[UUIDRole] = "uuid";
    roles[NameRole] = "name";
    roles[TemperatureRole] = "temperature";
    roles[HasTemperatureRole] = "hasTemperature";
    return roles;
}

int RoomListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_rooms.count();
}

QVariant RoomListModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_rooms.count())
        return QVariant();

    const Room* room = m_rooms[index.row()];

    switch (role) {
    case UUIDRole:
        return room->uuid();
    case NameRole:
        return room->name();
    case TemperatureRole:
        return room->temperature();
    case HasTemperatureRole:
        return room->hasTemperature();
    default:
        return QVariant();
    }
}

QModelIndex RoomListModel::index(int row, int column, const QModelIndex& parent) const
{
    return QAbstractListModel::index(row, column, parent);
}

#include <QtDebug>
void RoomListModel::append(Room* location)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_rooms.append(location);
    endInsertRows();

    connect(location, &Room::dataChanged, this, [&, location](){
        auto roomItr = std::find_if(
            m_rooms.begin(), m_rooms.end(), [&](Room* room) { return room->uuid() == location->uuid(); });

        auto rowIndex = std::distance(m_rooms.begin(), roomItr);
        auto modelIndex = index(rowIndex, 0);
        emit this->dataChanged(modelIndex, modelIndex);
    });
}

Qt::ItemFlags RoomListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool RoomListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_rooms.count())
        return false;

    Room* room = m_rooms[index.row()];

    switch (role) {
    case TemperatureRole:
        room->setTemperature(value.toInt());
        break;
    case UUIDRole:
    case NameRole:
    case HasTemperatureRole:
    default:
        break;
    }

    emit dataChanged(index, index, {role});

    return true;
}
