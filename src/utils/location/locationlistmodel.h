#ifndef LOCATIONLISTMODEL_H
#define LOCATIONLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

struct Coordinates {
    qreal longitude;
    qreal latitude;
};

class Location : public QObject {
    Q_OBJECT

    Q_PROPERTY(qint64 id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString state READ state CONSTANT)
    Q_PROPERTY(QString country READ country CONSTANT)
    Q_PROPERTY(qreal longitude READ longitude CONSTANT)
    Q_PROPERTY(qreal latitude READ latitude CONSTANT)

public:
    explicit Location(qint64 id, const QString& name, const QString& state, const QString& country,
        const Coordinates& coordinates, QObject* parent = nullptr)
        : QObject(parent)
        , m_id(id)
        , m_name(name)
        , m_state(state)
        , m_country(country)
        , m_coordinates(coordinates)
    {
    }

    qint64 id() const { return m_id; }
    QString name() const { return m_name; }
    QString state() const { return m_state; }
    QString country() const { return m_country; }
    qreal longitude() const { return m_coordinates.longitude; }
    qreal latitude() const { return m_coordinates.latitude; }

private:
    qint64 m_id = -1;
    QString m_name = "";
    QString m_state = "";
    QString m_country = "";
    Coordinates m_coordinates = { .0, .0 };
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
    Q_ENUM(LocationRoles)

    explicit LocationListModel(QObject* parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // NOTE (camar) : override for QML. Without it, QML sees only the 2-parameters and 3-parameters
    // versions.
    Q_INVOKABLE QModelIndex index(
        int row, int column = 0, const QModelIndex& parent = QModelIndex()) const override;

    void append(const Location* location);

    const Location* getFromId(qint64 id) const;

private:
    QList<const Location*> m_locations;
};

#endif // LOCATIONLISTMODEL_H
