#ifndef ABSTRACTWEATHERAPIACCESS_H
#define ABSTRACTWEATHERAPIACCESS_H

#include <QJsonDocument>
#include <QObject>

#include "weathersettings.h"

class AbstractWeatherAPIAccess : public QObject {
    Q_OBJECT

public:
    explicit AbstractWeatherAPIAccess(QObject* parent = nullptr);
    explicit AbstractWeatherAPIAccess(WeatherSettings* settings, QObject* parent = nullptr);
    virtual ~AbstractWeatherAPIAccess()
    {
    }

    virtual void requestData() = 0;

    WeatherSettings* settings() const
    {
        return m_settings;
    }

signals:
    void dataUpdated(QJsonDocument data);

protected:
    void setSettings(WeatherSettings* settings);

private:
    WeatherSettings* m_settings = nullptr;
};

#endif // ABSTRACTWEATHERAPIACCESS_H
