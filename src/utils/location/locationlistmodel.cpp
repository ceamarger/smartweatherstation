#include "locationlistmodel.h"

LocationListModel::LocationListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> LocationListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[StateRole] = "state";
    roles[CountryRole] = "country";
    roles[LongitudeRole] = "longitude";
    roles[LatitudeRole] = "latitude";
    return roles;
}

int LocationListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_locations.count();
}

QVariant LocationListModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_locations.count())
        return QVariant();

    const Location* location = m_locations[index.row()];

    switch (role) {
    case IdRole:
        return location->id();
    case NameRole:
        return location->name();
    case StateRole:
        return location->state();
    case CountryRole:
        return location->country();
    case LongitudeRole:
        return location->longitude();
    case LatitudeRole:
        return location->latitude();
    default:
        return QVariant();
    }
}

QModelIndex LocationListModel::index(int row, int column, const QModelIndex& parent) const
{
    return QAbstractListModel::index(row, column, parent);
}

void LocationListModel::append(const Location* location)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_locations.append(location);
    endInsertRows();
}

const Location* LocationListModel::getFromId(qint64 id) const
{
    auto it = std::find_if(m_locations.begin(), m_locations.end(),
        [&id](const Location* location) { return location->id() == id; });

    return it != m_locations.end() ? *it : nullptr;
}
