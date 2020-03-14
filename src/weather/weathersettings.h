#ifndef WEATHERSETTINGS_H
#define WEATHERSETTINGS_H

#include <QObject>
#include <QSettings>

/*!
 * \class WeatherSettings
 * \brief A class that can be used to store settings in a file.
 *
 * WeatherSettings class can be used to store settings in a file.
 * The file is formated as an INI file.
 */
class WeatherSettings : public QObject {
    Q_OBJECT

public:
    explicit WeatherSettings(const QString& filename, QObject* parent = nullptr);

    QVariant value(
        const QString& group, const QString& key, const QVariant& defaultValue = QVariant()) const;
    void setValue(const QString& group, const QString& key, const QVariant& value);

signals:

private:
    QSettings* m_settings = nullptr;
};

#endif // WEATHERSETTINGS_H
