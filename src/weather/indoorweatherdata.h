#ifndef INDOORWEATHERDATA_H
#define INDOORWEATHERDATA_H

#include <QList>
#include <QObject>
#include <optional>

#include "room.h"

class IndoorWeatherData : public QObject {
    Q_OBJECT

    Q_PROPERTY(Room* mainRoom READ mainRoom NOTIFY mainRoomChanged)
    Q_PROPERTY(RoomListModel* rooms READ rooms NOTIFY newRoomReceived)

public:
    explicit IndoorWeatherData(QObject* parent = nullptr);

    Room* mainRoom();
    Room* roomByUuid(const QString& uuid);
    RoomListModel* rooms() { return &m_rooms; }

    Q_INVOKABLE void registerRoom(const QString& uuid, const QString& name = QString());

    void setMainRoomUuid(const QString& mainRoomUuid);
    void setTemperature(const QString& uuid, quint16 temperature);

    static bool isValidUuid(const QString& uuid);

signals:
    void temperatureChanged();
    void mainRoomChanged();
    void newRoomReceived(const QString& uuid);

private:
    void appendRoom(Room* const& room);

    QString m_mainRoomUuid = QString();
    RoomListModel m_rooms = RoomListModel();
};

#endif // INDOORWEATHERDATA_H
