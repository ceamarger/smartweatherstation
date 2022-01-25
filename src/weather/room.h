#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QAbstractListModel>

class Room : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString uuid READ uuid CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(quint16 temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(bool hasTemperature READ hasTemperature NOTIFY temperatureChanged)

public:
    explicit Room(QObject* parent = nullptr);
    explicit Room(const QString& uuid, const QString& name = QString(), QObject* parent = nullptr);

    QString uuid() const { return m_uuid; }
    QString name() const { return m_name; }
    quint16 temperature() const { return m_temperature.value_or(0); }
    bool hasTemperature() const { return m_temperature.has_value(); }

    void setTemperature(quint16 temperature);

signals:
    void temperatureChanged();
    void dataChanged();

private:
    QString m_uuid = QString();
    QString m_name = QString();
    std::optional<quint16> m_temperature = std::nullopt; // centiKelvin (°K * 100)
};


class RoomListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum RoomRoles {
        UUIDRole = Qt::UserRole + 1,
        NameRole,
        TemperatureRole,
        HasTemperatureRole
    };
    Q_ENUM(RoomRoles)

    explicit RoomListModel(QObject* parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    // NOTE (camar) : override for QML. Without it, QML sees only the 2-parameters and 3-parameters
    // versions.
    Q_INVOKABLE QModelIndex index(
            int row, int column = 0, const QModelIndex& parent = QModelIndex()) const override;

    void append(Room* location);

    const QList<Room*>& list() const { return m_rooms; }

private:
    QList<Room*> m_rooms;
};
#endif // ROOM_H
