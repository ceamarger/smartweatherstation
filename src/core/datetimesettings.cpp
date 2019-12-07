#include "datetimesettings.h"

#include <QDateTime>
#include <QLocale>

DateTimeSettings::DateTimeSettings(QObject *parent) : QObject(parent)
{
    connect(&m_clockTimer, &QTimer::timeout, this, &DateTimeSettings::onClockTimerTimeout);
    m_clockTimer.setInterval(ClockInterval);
    m_clockTimer.start();
}

QString DateTimeSettings::currentDate()
{
    return QDate::currentDate().toString(Qt::DateFormat::SystemLocaleLongDate);
}

QString DateTimeSettings::currentTime()
{
    return QTime::currentTime().toString(Qt::DateFormat::SystemLocaleShortDate);
}

void DateTimeSettings::onClockTimerTimeout()
{
    emit dateTimeChanged();
}
