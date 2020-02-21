#ifndef DATETIMESETTINGS_H
#define DATETIMESETTINGS_H

#include <QObject>
#include <QString>
#include <QTimer>

class DateTimeSettings : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString currentDate READ currentDate NOTIFY dateTimeChanged)
    Q_PROPERTY(QString currentTime READ currentTime NOTIFY dateTimeChanged)

public:
    explicit DateTimeSettings(QObject* parent = nullptr);

    static QString currentDate();
    static QString currentTime();

signals:
    void dateTimeChanged();

private slots:
    void onClockTimerTimeout();

private:
    static constexpr int ClockInterval = 1000;

    QTimer m_clockTimer;
};

#endif // DATETIMESETTINGS_H
