#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QJsonDocument>
#include <QObject>
#include <QTime>

#include "abstractweatherapiaccess.h"
#include "indoorweatherdata.h"
#include "settings/weathersettings.h"

// NOTE (camar) : Maybe better to make OutdoorData and IndoorData structs some classes to access it
// from QML instead of having the Q_PROPERTIES into WeatherData class ?
struct OutdoorData {
    AbstractWeatherAPIAccess* api = nullptr;
    quint16 temperature = 0; // centiKelvin (°K * 100)
    quint8 humidityPercentage = 0;
    QTime sunriseTime = QTime(0, 0);
    QTime sunsetTime = QTime(0, 0);
};

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
    Q_PROPERTY(IndoorWeatherData* indoorWeatherData READ indoorWeatherData CONSTANT)
    Q_PROPERTY(AbstractWeatherAPIAccess* api READ api CONSTANT)
    Q_PROPERTY(WeatherSettings* settings READ settings CONSTANT)

public:
    explicit WeatherData(WeatherSettings* settings, QObject* parent = nullptr);

    quint16 outdoorTemperature() const { return m_outdoorData.temperature; }
    quint8 humidityPercentage() const { return m_outdoorData.humidityPercentage; }
    QTime sunriseTime() const { return m_outdoorData.sunriseTime; }
    QTime sunsetTime() const { return m_outdoorData.sunsetTime; }
    AbstractWeatherAPIAccess* api() const { return m_outdoorData.api; }

    IndoorWeatherData* indoorWeatherData() { return &m_indoorWeatherData; }

    WeatherSettings* settings() const { return m_settings; }

    void setOutdoorTemperature(quint16 outdoorTemperature);
    void setHumidityPercentage(quint8 humidityPercentage);
    void setSunriseTime(QTime sunriseTime);
    void setSunsetTime(QTime sunsetTime);

signals:
    void outdoorTemperatureChanged();
    void humidityPercentageChanged();
    void sunriseTimeChanged();
    void sunsetTimeChanged();

private slots:
    void parseReceivedJsonData(QJsonDocument jsonData);

private:
    void setAPI(AbstractWeatherAPIAccess* api);

    OutdoorData m_outdoorData;
    IndoorWeatherData m_indoorWeatherData;

    WeatherSettings* m_settings = nullptr;
};

#endif // WEATHERDATA_H
