#ifndef ROOM_H
#define ROOM_H

#include <QObject>

class Room : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString uuid READ uuid CONSTANT)
    Q_PROPERTY(quint16 temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(bool hasTemperature READ hasTemperature NOTIFY temperatureChanged)

public:
    explicit Room(QObject* parent = nullptr);
    explicit Room(const QString& uuid, const QString& name = QString(), QObject* parent = nullptr);

    QString uuid() const { return m_uuid; }
    QString name() const { return m_name; }
    quint16 temperature() { return m_temperature.value_or(0); }
    bool hasTemperature() { return m_temperature.has_value(); }

    void setTemperature(quint16 temperature);

signals:
    void temperatureChanged();

private:
    QString m_uuid = QString();
    QString m_name = QString();
    std::optional<quint16> m_temperature = std::nullopt; // centiKelvin (°K * 100)
};

#endif // ROOM_H
