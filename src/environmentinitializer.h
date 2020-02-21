#ifndef ENVIRONMENTINITIALIZER_H
#define ENVIRONMENTINITIALIZER_H

#include <QQmlContext>
#include "core/datetimesettings.h"
#include "weather/weatherdata.h"
#include "weather/weathersettings.h"

class EnvironmentInitializer
{
public:
    static EnvironmentInitializer& getInstance();

    void initialize(QQmlContext* context);

private:
    EnvironmentInitializer() = default;
    ~EnvironmentInitializer();
    EnvironmentInitializer(const EnvironmentInitializer&) = delete;
    EnvironmentInitializer& operator=(const EnvironmentInitializer&) = delete;

    void initializeEnvironment();
    void initializeContext(QQmlContext* context);
    void registerQMLTypes();

    DateTimeSettings m_dateTimeSettings;
    WeatherSettings *m_weatherSettings;
    WeatherData* m_weatherData = nullptr;
};

#endif // ENVIRONMENTINITIALIZER_H
