#ifndef WEATHERSETTINGS_H
#define WEATHERSETTINGS_H

#include <QObject>
#include <QSettings>

class WeatherSettings : public QObject {
    Q_OBJECT

public:
    explicit WeatherSettings(const QString& filename, QObject* parent = nullptr);

    QVariant value(
        const QString& group, const QString& key, const QVariant& defaultValue = QVariant()) const;
    void setValue(const QString& group, const QString& key, const QVariant& value);

signals:

private:
    QSettings* m_settings;
};

#endif // WEATHERSETTINGS_H
