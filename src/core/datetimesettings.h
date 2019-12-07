#ifndef DATETIMESETTINGS_H
#define DATETIMESETTINGS_H

#include <QObject>
#include <QString>

class DateTimeSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString currentDate READ currentDate CONSTANT)
    Q_PROPERTY(QString currentTime READ currentTime CONSTANT)

public:
    explicit DateTimeSettings(QObject *parent = nullptr);

    static QString currentDate();
    static QString currentTime();

signals:

public slots:
};

#endif // DATETIMESETTINGS_H
