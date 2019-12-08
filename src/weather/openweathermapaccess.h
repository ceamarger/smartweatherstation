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
    static QString AppId;
};

namespace OpenWeatherMapAccessKeys {

static QString Main = "main";
static QString Sys = "sys";
static QString Temperature = "temp";
static QString Humidity = "humidity";
static QString Sunset = "sunset";
static QString Sunrise = "sunrise";

}

#endif // OPENWEATHERMAPACCESS_H
