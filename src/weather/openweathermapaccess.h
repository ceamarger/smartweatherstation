#ifndef OPENWEATHERMAPACCESS_H
#define OPENWEATHERMAPACCESS_H

#include "abstractweatherapiaccess.h"

#include <QNetworkAccessManager>
#include <QTimer>

class OpenWeatherMapAccess : public AbstractWeatherAPIAccess
{
public:
    explicit OpenWeatherMapAccess(QObject *parent = nullptr);

private slots:
    void requestData() override;
    void onManagerReplyReceived(QNetworkReply *reply);

private:
    QNetworkAccessManager m_accessManager;
    QTimer m_refreshtimer;

    static const std::chrono::minutes RefreshInterval;
};

namespace  OpenWeatherMapSettingsParameters {

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
