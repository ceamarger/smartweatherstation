#ifndef ENVIRONMENTINITIALIZER_H
#define ENVIRONMENTINITIALIZER_H

#include <QQmlContext>

#include "core/datetimesettings.h"
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

    DateTimeSettings m_dateTimeSettings;
    Weather m_weather;
};

#endif // ENVIRONMENTINITIALIZER_H
