#ifndef OPENWEATHERMAPACCESS_H
#define OPENWEATHERMAPACCESS_H

#include "abstractweatherapiaccess.h"

#include <QNetworkAccessManager>
#include <QTimer>

class OpenWeatherMapAccess : public AbstractWeatherAPIAccess
{
    Q_OBJECT

    Q_PROPERTY(QString appId READ appId CONSTANT)

public:
    explicit OpenWeatherMapAccess(WeatherSettings *settings, QObject *parent = nullptr);

    const QString appId() const;

private slots:
    void requestData() override;
    void onManagerReplyReceived(QNetworkReply *reply);

private:
    QNetworkAccessManager m_accessManager;
    QTimer m_refreshtimer;

    static const std::chrono::minutes RefreshInterval;
};

namespace  OpenWeatherMapSettingsParameters {

static const QString GroupName = "OWMSettings";
static const QString AppId = "appId";

}

namespace OpenWeatherMapAccessKeys {

static const QString Main = "main";
static const QString Sys = "sys";
static const QString Temperature = "temp";
static const QString Humidity = "humidity";
static const QString Sunset = "sunset";
static const QString Sunrise = "sunrise";

}

#endif // OPENWEATHERMAPACCESS_H
