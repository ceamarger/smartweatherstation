#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>

#include "weatherdata.h"
#include "weathersettings.h"

class Weather : public QObject {
    Q_OBJECT

    Q_PROPERTY(WeatherSettings* settings READ settings CONSTANT)
    Q_PROPERTY(WeatherData* data READ data CONSTANT)

public:
    explicit Weather(QObject* parent = nullptr);
    Weather(const QString& settingsFileName, QObject* parent = nullptr);

    WeatherSettings* settings() const;
    WeatherData* data() const;

private:
    void registerQMLTypes();

    WeatherSettings* m_settings = nullptr;
    WeatherData* m_data = nullptr;

    static const QString WeatherSettingsFileName;
};

#endif // WEATHER_H
