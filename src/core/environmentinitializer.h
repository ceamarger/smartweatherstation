#ifndef ENVIRONMENTINITIALIZER_H
#define ENVIRONMENTINITIALIZER_H

#include <QQmlContext>
#include "datetimesettings.h"

class EnvironmentInitializer
{
public:
    static EnvironmentInitializer& getInstance();

    void initializeContext(QQmlContext* context);

    DateTimeSettings* dateTimeSettings() { return &m_dateTimeSettings; }

private:
    EnvironmentInitializer() = default;
    ~EnvironmentInitializer() = default;
    EnvironmentInitializer(const EnvironmentInitializer&) = delete;
    EnvironmentInitializer& operator=(const EnvironmentInitializer&) = delete;

    DateTimeSettings m_dateTimeSettings;
};

#endif // ENVIRONMENTINITIALIZER_H
