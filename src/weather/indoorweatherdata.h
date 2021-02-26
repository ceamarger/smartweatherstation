#ifndef INDOORWEATHERDATA_H
#define INDOORWEATHERDATA_H

#include <QList>
#include <QObject>
#include <optional>

#include "room.h"

class IndoorWeatherData : public QObject {
    Q_OBJECT

    Q_PROPERTY(Room* mainRoom READ mainRoom NOTIFY mainRoomChanged)

public:
    explicit IndoorWeatherData(QObject* parent = nullptr);

    Room* mainRoom();
    Room* roomByUuid(const QString& uuid);
    QList<Room*> rooms() const { return m_rooms; }

    void appendRoom(Room* const& room);
    void registerRoom(const QString& uuid, const QString& name = QString());

    void setMainRoomUuid(const QString& mainRoomUuid);
    void setTemperature(const QString& uuid, quint16 temperature);

    static bool isValidUuid(const QString& uuid);

signals:
    void temperatureChanged();
    void mainRoomChanged();

private:
    QString m_mainRoomUuid = QString();
    QList<Room*> m_rooms = QList<Room*>();
};

#endif // INDOORWEATHERDATA_H
