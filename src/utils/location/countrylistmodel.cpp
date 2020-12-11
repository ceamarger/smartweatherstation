#include "countrylistmodel.h"

CountryListModel::CountryListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> CountryListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NumericCodeRole] = "numericCode";
    roles[NameRole] = "name";
    roles[Alpha2CodeRole] = "alpha2Code";
    roles[Alpha3CodeRole] = "alpha3Code";
    roles[RegionRole] = "region";
    return roles;
}

int CountryListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_countries.count();
}

QVariant CountryListModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_countries.count())
        return QVariant();

    const Country* country = m_countries[index.row()];

    switch (role) {
    case NumericCodeRole:
        return country->numericCode();
    case NameRole:
        return country->name();
    case Alpha2CodeRole:
        return country->alpha2Code();
    case Alpha3CodeRole:
        return country->alpha3Code();
    case RegionRole:
        return country->region();
    default:
        return QVariant();
    }
}

QModelIndex CountryListModel::index(int row, int column, const QModelIndex& parent) const
{
    return QAbstractListModel::index(row, column, parent);
}

void CountryListModel::append(const Country* location)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_countries.append(location);
    endInsertRows();
}
