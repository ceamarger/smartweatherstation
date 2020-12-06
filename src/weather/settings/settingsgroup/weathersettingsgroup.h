#ifndef WEATHERSETTINGSGROUP_H
#define WEATHERSETTINGSGROUP_H

#include "settingsgroup.h"
#include <QObject>

class WeatherSettingsGroup : public SettingsGroup {
    Q_OBJECT

public:
    explicit WeatherSettingsGroup(WeatherSettings* settings, QObject* parent = nullptr);
};

namespace WeatherSettingsParameters {

static const QString GroupName = "WeatherSettings";
static const QString Location = "location";
}
#endif // WEATHERSETTINGSGROUP_H
