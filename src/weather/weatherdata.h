#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QJsonDocument>
#include <QObject>
#include <QTime>

#include "abstractweatherapiaccess.h"
#include "settings/weathersettings.h"

/*!
 * \brief This class contains weather data.
 *
 * This also is an accessor to the API. But this should change.
 */
class WeatherData : public QObject {
    Q_OBJECT
    Q_PROPERTY(quint16 outdoorTemperature READ outdoorTemperature NOTIFY outdoorTemperatureChanged)
    Q_PROPERTY(quint8 humidityPercentage READ humidityPercentage NOTIFY humidityPercentageChanged)
    Q_PROPERTY(QTime sunriseTime READ sunriseTime NOTIFY sunriseTimeChanged)
    Q_PROPERTY(QTime sunsetTime READ sunsetTime NOTIFY sunsetTimeChanged)
    Q_PROPERTY(quint16 indoorTemperature READ indoorTemperature NOTIFY indoorTemperatureChanged)

    Q_PROPERTY(AbstractWeatherAPIAccess* api READ api CONSTANT)
    Q_PROPERTY(WeatherSettings* settings READ settings CONSTANT)

public:
    explicit WeatherData(WeatherSettings* settings, QObject* parent = nullptr);

    quint16 outdoorTemperature() const { return m_outdoorTemperature; }
    quint8 humidityPercentage() const { return m_humidityPercentage; }
    QTime sunriseTime() const { return m_sunriseTime; }
    QTime sunsetTime() const { return m_sunsetTime; }
    quint16 indoorTemperature() const { return m_indoorTemperature; }
    AbstractWeatherAPIAccess* api() const { return m_api; }
    WeatherSettings* settings() const { return m_settings; }

signals:
    void outdoorTemperatureChanged();
    void humidityPercentageChanged();
    void sunriseTimeChanged();
    void sunsetTimeChanged();
    void indoorTemperatureChanged();

private slots:
    void parseReceivedJsonData(QJsonDocument jsonData);

private:
    void setAPI(AbstractWeatherAPIAccess* api);

    void setOutdoorTemperature(quint16 outdoorTemperature);
    void setHumidityPercentage(quint8 humidityPercentage);
    void setSunriseTime(QTime sunriseTime);
    void setSunsetTime(QTime sunsetTime);
    void setIndoorTemperature(quint16 indoorTemperature);

    // NOTE (camar) : Maybe better to separate outdoor and indoor data
    // outdoor
    AbstractWeatherAPIAccess* m_api = nullptr;
    quint16 m_outdoorTemperature = 0; // centiKelvin (°K * 100)
    quint8 m_humidityPercentage = 0;
    QTime m_sunriseTime = QTime(0, 0);
    QTime m_sunsetTime = QTime(0, 0);

    // indoor
    quint16 m_indoorTemperature = 0; // centiKelvin (°K * 100)

    WeatherSettings* m_settings = nullptr;
};

#endif // WEATHERDATA_H
