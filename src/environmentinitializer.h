#ifndef ENVIRONMENTINITIALIZER_H
#define ENVIRONMENTINITIALIZER_H

#include <QQmlContext>
#include "core/datetimesettings.h"
#include "weather/weatherdata.h"

class EnvironmentInitializer
{
public:
    static EnvironmentInitializer& getInstance();

    void initializeContext(QQmlContext* context);

    DateTimeSettings* dateTimeSettings() { return &m_dateTimeSettings; }
    WeatherData* weatherData() { return &m_weatherData; }

private:
    EnvironmentInitializer() = default;
    ~EnvironmentInitializer() = default;
    EnvironmentInitializer(const EnvironmentInitializer&) = delete;
    EnvironmentInitializer& operator=(const EnvironmentInitializer&) = delete;

    DateTimeSettings m_dateTimeSettings;
    WeatherData m_weatherData;
};

#endif // ENVIRONMENTINITIALIZER_H
