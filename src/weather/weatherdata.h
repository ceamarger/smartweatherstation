#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QObject>
#include <QTime>

class WeatherData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 outdoorTemperature READ outdoorTemperature NOTIFY outdoorTemperatureChanged)
    Q_PROPERTY(quint8 humidityPercentage READ humidityPercentage NOTIFY humidityPercentageChanged)
    Q_PROPERTY(QTime sunriseTime READ sunriseTime NOTIFY sunriseTimeChanged)
    Q_PROPERTY(QTime sunsetTime READ sunsetTime NOTIFY sunsetTimeChanged)

public:
    explicit WeatherData(QObject *parent = nullptr);

    quint16 outdoorTemperature() const { return m_outdoorTemperature; }
    quint8 humidityPercentage() const { return m_humidityPercentage; }
    QTime sunriseTime() const { return m_sunriseTime; }
    QTime sunsetTime() const { return m_sunsetTime; }

    void setOutdoorTemperature(quint16 outdoorTemperature);
    void setHumidityPercentage(quint8 humidityPercentage);
    void setSunriseTime(QTime sunriseTime);
    void setSunsetTime(QTime sunsetTime);

signals:
    void outdoorTemperatureChanged();
    void humidityPercentageChanged();
    void sunriseTimeChanged();
    void sunsetTimeChanged();

private:
    quint16 m_outdoorTemperature = 0; // centiKelvin (°K * 100)
    quint8 m_humidityPercentage = 0;
    QTime m_sunriseTime = QTime(0,0);
    QTime m_sunsetTime = QTime(0,0);
};

#endif // WEATHERDATA_H
