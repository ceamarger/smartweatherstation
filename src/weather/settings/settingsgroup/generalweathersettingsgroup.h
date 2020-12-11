#ifndef GENERALWEATHERSETTINGSGROUP_H
#define GENERALWEATHERSETTINGSGROUP_H

#include "settingsgroup.h"
#include <QObject>

class GeneralWeatherSettingsGroup : public SettingsGroup {
    Q_OBJECT

    Q_PROPERTY(int locationId READ locationId WRITE setLocationId NOTIFY locationIdChanged)
public:
    explicit GeneralWeatherSettingsGroup(WeatherSettings* settings, QObject* parent = nullptr);

    int locationId() const;

    // NOTE (camar) : locationId is the ID of the location contained in citylist.json file
    void setLocationId(int newLocationId);

signals:
    void locationIdChanged(int locationId);
};

namespace GeneralWeatherSettingsParameters {

static const QString GroupName = "GeneralWeatherSettings";
static const QString LocationId = "locationId";
}
#endif // GENERALWEATHERSETTINGSGROUP_H
