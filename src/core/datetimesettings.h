#ifndef DATETIMESETTINGS_H
#define DATETIMESETTINGS_H

#include <QObject>
#include <QString>

class DateTimeSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString currentDate READ currentDate CONSTANT)

public:
    explicit DateTimeSettings(QObject *parent = nullptr);

    QString currentDate();

signals:

public slots:
};

#endif // DATETIMESETTINGS_H
