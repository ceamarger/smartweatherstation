#include "openweathermapaccess.h"
#include "weatherdatajsonkeys.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

const std::chrono::minutes OpenWeatherMapAccess::RefreshInterval = std::chrono::minutes(1);

OpenWeatherMapAccess::OpenWeatherMapAccess(WeatherSettings* settings, QObject* parent)
    : AbstractWeatherAPIAccess(settings, parent)
{
    connect(&m_accessManager, &QNetworkAccessManager::finished, this,
        &OpenWeatherMapAccess::onManagerReplyReceived);

    m_refreshTimer.setInterval(std::chrono::milliseconds(RefreshInterval).count());
    m_refreshTimer.setSingleShot(true);
    connect(&m_refreshTimer, &QTimer::timeout, this, &OpenWeatherMapAccess::requestData);

    requestData();
}

const QString OpenWeatherMapAccess::appId() const
{
    using namespace OpenWeatherMapSettingsParameters;
    return settings() ? settings()->value(GroupName, AppId).toString() : "";
}

void OpenWeatherMapAccess::requestData()
{
    qDebug() << "Requesting weather data...";

    QString urlString = "http://api.openweathermap.org/data/2.5/";
    // Append City (TODO : manage city changes)
    urlString.append("weather?q=Lyon");
    // AppId should be 4a987c6635e6fe3bc8b97cfd6fdda8f1 but needs settings menu
    urlString.append("&appid=" + appId());
    QUrl url(urlString);

    QNetworkRequest request(url);
    m_accessManager.get(request);

    m_refreshTimer.start();
}

void OpenWeatherMapAccess::onManagerReplyReceived(QNetworkReply* reply)
{
    using namespace OpenWeatherMapAccessKeys;

    qDebug() << "Weather data received !";
    QByteArray binaryData = reply->readAll();
    reply->deleteLater();

    QJsonDocument document = QJsonDocument::fromJson(binaryData);

    QJsonDocument finalJsonDocument;
    QJsonObject finalJsonObject;
    finalJsonObject[WeatherDataKeys::OutdoorTemperature] = document[Main][Temperature];
    finalJsonObject[WeatherDataKeys::Humidity] = document[Main][Humidity];
    finalJsonObject[WeatherDataKeys::Sunrise] = document[Sys][Sunrise];
    finalJsonObject[WeatherDataKeys::Sunset] = document[Sys][Sunset];
    finalJsonDocument.setObject(finalJsonObject);

    emit dataUpdated(finalJsonDocument);
}
