#ifndef ABSTRACTWEATHERAPIACCESS_H
#define ABSTRACTWEATHERAPIACCESS_H

#include <QJsonDocument>
#include <QObject>

#include "settings/weathersettings.h"

/*!
 * \brief An abstract class that provides basics to have differents weather APIs
 *
 * If a class inherits from AbstractWeatherAPIAccess, make sure to overwrite \a requestData().
 * Moreover, it is your own responsibility to emit or not the \a dataUpdated() signal.
 * For now - but should change - this also your own responsibility to call \a requestData().
 */

class AbstractWeatherAPIAccess : public QObject {
    Q_OBJECT

public:
    explicit AbstractWeatherAPIAccess(QObject* parent = nullptr);
    explicit AbstractWeatherAPIAccess(WeatherSettings* settings, QObject* parent = nullptr);
    virtual ~AbstractWeatherAPIAccess() {}

    virtual void requestData() = 0;

    WeatherSettings* settings() const { return m_settings; }

signals:
    /*!
     * \brief Signal to emit when data has been received from the API
     * \param data json data to transmit
     */
    void dataUpdated(QJsonDocument data);

private:
    WeatherSettings* m_settings = nullptr;
};

#endif // ABSTRACTWEATHERAPIACCESS_H
