#ifndef ENVIRONMENTINITIALIZER_H
#define ENVIRONMENTINITIALIZER_H

#include <QQmlContext>

#include "core/datetimesettings.h"
#include "utils/location/locationfinder.h"
#include "weather/weather.h"

class EnvironmentInitializer {
public:
    static EnvironmentInitializer& getInstance();

    void initialize(QQmlContext* context);

private:
    EnvironmentInitializer() = default;
    ~EnvironmentInitializer() = default;
    EnvironmentInitializer(const EnvironmentInitializer&) = delete;
    EnvironmentInitializer& operator=(const EnvironmentInitializer&) = delete;

    void initializeContext(QQmlContext* context);
    void initializeLocations();

    DateTimeSettings m_dateTimeSettings;
    Weather m_weather;
    LocationFinder m_locationFinder;
};

#endif // ENVIRONMENTINITIALIZER_H
