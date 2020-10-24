#ifndef TEMPERATURESETTINGSGROUP_H
#define TEMPERATURESETTINGSGROUP_H

#include "settingsgroup.h"
#include <QObject>

class TemperatureSettingsGroup : public SettingsGroup {
    Q_OBJECT

    Q_PROPERTY(TemperatureUnit unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(QString unitString READ unitString NOTIFY unitChanged)
    Q_PROPERTY(QStringList availableUnitsStrings READ availableUnitsStrings CONSTANT)

public:
    enum class TemperatureUnit { Kelvin, Celsius, Fahrenheit };
    Q_ENUM(TemperatureUnit)

    explicit TemperatureSettingsGroup(WeatherSettings* settings, QObject* parent = nullptr);

    TemperatureUnit unit() const;
    QString unitString() const;
    static QString unitFullName(TemperatureUnit unit);

    static QStringList availableUnitsStrings();
    Q_INVOKABLE static TemperatureUnit availableUnitAtIndex(int index);
    Q_INVOKABLE static int availableUnitIndex(TemperatureUnit unit);

    void setUnit(TemperatureUnit newUnit);

signals:
    void unitChanged(TemperatureUnit unit);

private:
    static QList<TemperatureUnit> const AvailableUnits;
};

namespace TemperatureSettingsParameters {

static const QString GroupName = "TemperatureSettings";
static const QString Unit = "unit";
}
#endif // TEMPERATURESETTINGSGROUP_H
