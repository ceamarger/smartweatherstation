#ifndef WEATHERSETTINGSGROUP_H
#define WEATHERSETTINGSGROUP_H

#include "settingsgroup.h"
#include <QObject>

class WeatherSettingsGroup : public SettingsGroup {
    Q_OBJECT

    Q_PROPERTY(int locationId READ locationId WRITE setLocationId NOTIFY locationIdChanged)
public:
    explicit WeatherSettingsGroup(WeatherSettings* settings, QObject* parent = nullptr);

    int locationId() const;

    // NOTE (camar) : locationId is the ID of the location contained in citylist.json file
    void setLocationId(int newLocationId);

signals:
    void locationIdChanged(int locationId);
};

namespace WeatherSettingsParameters {

static const QString GroupName = "GeneralWeatherSettings";
static const QString LocationId = "locationId";
}
#endif // WEATHERSETTINGSGROUP_H
