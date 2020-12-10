#include "openweathermapaccess.h"
#include "weatherdatajsonkeys.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

#include "settings/settingsgroup/weathersettingsgroup.h"

std::chrono::seconds OpenWeatherMapAccess::RefreshInterval = std::chrono::minutes(1);

/*!
 * \brief Create an OpenWeatherMapAccess object with the given \a parent and \a settings
 * \param settings The settings object that contains open weather map api settings (appId, etc...)
 * \param parent Parent of the object
 *
 * This constructor immediately request new data to the API.
 * periodically.
 *
 */
OpenWeatherMapAccess::OpenWeatherMapAccess(WeatherSettings* settings, QObject* parent)
    : AbstractWeatherAPIAccess(settings, parent)
{
    connect(&m_accessManager, &QNetworkAccessManager::finished, this,
        &OpenWeatherMapAccess::onManagerReplyReceived);

    m_refreshTimer.setInterval(
        static_cast<int>(std::chrono::milliseconds(RefreshInterval).count()));
    m_refreshTimer.setSingleShot(true);
    connect(&m_refreshTimer, &QTimer::timeout, this, &OpenWeatherMapAccess::requestData);

    requestData();
}

/*!
 * \brief Get the OpenWeatherMap application Id
 * \return the appId used to access the OpenWeatherMap API
 */
const QString OpenWeatherMapAccess::appId() const
{
    // TODO (camar) : use new SettingsGroup class
    using namespace OpenWeatherMapSettingsParameters;
    return settings() ? settings()->value(GroupName, AppId).toString() : "";
}

/*!
 * \brief Request data to the OpenWeatherMap API
 *
 * This function is called periodically after its first call.
 */
void OpenWeatherMapAccess::requestData()
{
    qDebug() << "Requesting weather data...";

    auto locationId
        = settings() ? QString::number(settings()->generalWeatherSettings()->locationId()) : "";
    QString urlString = "http://api.openweathermap.org/data/2.5/";
    urlString.append("weather?id=" + locationId);
    // AppId should be 4a987c6635e6fe3bc8b97cfd6fdda8f1 (used for test only) but needs settings menu
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

/*!
 * \brief Set the interval between two request
 * \param seconds number of seconds between two requests
 */
void OpenWeatherMapAccess::setRefreshInterval(std::chrono::seconds seconds)
{
    RefreshInterval = seconds;
    m_refreshTimer.setInterval(
        static_cast<int>(std::chrono::milliseconds(RefreshInterval).count()));
}
