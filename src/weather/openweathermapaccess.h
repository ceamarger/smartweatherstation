#ifndef OPENWEATHERMAPACCESS_H
#define OPENWEATHERMAPACCESS_H

#include "abstractweatherapiaccess.h"

#include <QNetworkAccessManager>
#include <QTimer>

/*!
 * \brief This class is used to access OpenWeatherMap API and request jsonData to it
 */
class OpenWeatherMapAccess : public AbstractWeatherAPIAccess {
    Q_OBJECT

    Q_PROPERTY(QString appId READ appId CONSTANT)

public:
    explicit OpenWeatherMapAccess(WeatherSettings* settings, QObject* parent = nullptr);
    ~OpenWeatherMapAccess() override {}

    void setRefreshInterval(std::chrono::seconds seconds);

    const QString appId() const;

private slots:
    void requestData() override;
    void onManagerReplyReceived(QNetworkReply* reply);

private:
    QNetworkAccessManager m_accessManager;
    QTimer m_refreshTimer;

    static std::chrono::seconds RefreshInterval;
};

namespace OpenWeatherMapSettingsParameters {

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
