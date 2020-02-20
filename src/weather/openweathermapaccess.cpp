#include "openweathermapaccess.h"
#include "weatherdatajsonkeys.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

const std::chrono::minutes OpenWeatherMapAccess::RefreshInterval = std::chrono::minutes(1);

OpenWeatherMapAccess::OpenWeatherMapAccess(QObject *parent) : AbstractWeatherAPIAccess(parent)
{
    setSettings(new QSettings("OWMSettings", QSettings::IniFormat, this));

    connect(&m_accessManager, &QNetworkAccessManager::finished, this, &OpenWeatherMapAccess::onManagerReplyReceived);

    m_refreshtimer.setInterval(std::chrono::milliseconds(RefreshInterval).count());
    m_refreshtimer.setSingleShot(true);
    connect(&m_refreshtimer, &QTimer::timeout, this, &OpenWeatherMapAccess::requestData);

    requestData();
}

void OpenWeatherMapAccess::requestData()
{
    qDebug() << "Requesting weather data...";

    const QString appId = settings()->value(OpenWeatherMapSettingsParameters::AppId).toString();

    QString urlString = "http://api.openweathermap.org/data/2.5/";
    urlString.append("weather?q=Lyon"); // Append City (TODO : manage city changes)
    urlString.append("&appid=" + appId); // should be 4a987c6635e6fe3bc8b97cfd6fdda8f1 but needs settings menu
    QUrl url(urlString);

    QNetworkRequest request(url);
    m_accessManager.get(request);

    m_refreshtimer.start();
}

void OpenWeatherMapAccess::onManagerReplyReceived(QNetworkReply *reply)
{
    using namespace OpenWeatherMapAccessKeys;

    qDebug() << "Weather data received !";
    QByteArray binaryData = reply->readAll();
    reply->deleteLater();

    QJsonDocument document  = QJsonDocument::fromJson(binaryData);

    QJsonDocument finalJsonDocument;
    QJsonObject finalJsonObject;
    finalJsonObject[WeatherDataKeys::OutdoorTemperature] = document[Main][Temperature];
    finalJsonObject[WeatherDataKeys::Humidity] = document[Main][Humidity];
    finalJsonObject[WeatherDataKeys::Sunrise] = document[Sys][Sunrise];
    finalJsonObject[WeatherDataKeys::Sunset] = document[Sys][Sunset];
    finalJsonDocument.setObject(finalJsonObject);

    emit dataUpdated(finalJsonDocument);
}


