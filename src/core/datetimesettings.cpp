#include "datetimesettings.h"

#include <QDateTime>
#include <QLocale>

DateTimeSettings::DateTimeSettings(QObject *parent) : QObject(parent)
{

}

QString DateTimeSettings::currentDate()
{
    return QDate::currentDate().toString(Qt::DateFormat::SystemLocaleLongDate);
}

QString DateTimeSettings::currentTime()
{
    return QTime::currentTime().toString(Qt::DateFormat::SystemLocaleShortDate);
}
