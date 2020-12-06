#ifndef LOCATIONLISTMODEL_H
#define LOCATIONLISTMODEL_H

#include <QAbstractListModel>

struct Coordinates {
    qreal longitude;
    qreal latitude;
};

struct Location {
    qint64 id = -1;
    QString name = "";
    QString state = "";
    QString country = "";
    Coordinates coordinates = { .0, .0 };
};

class LocationListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum LocationRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        StateRole,
        CountryRole,
        LongitudeRole,
        LatitudeRole
    };

    explicit LocationListModel(QObject* parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void append(const Location& location);

private:
    QList<Location> m_locations;
};

#endif // LOCATIONLISTMODEL_H
