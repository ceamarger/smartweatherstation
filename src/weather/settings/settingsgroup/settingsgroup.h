#ifndef SETTINGSGROUP_H
#define SETTINGSGROUP_H

#include <QObject>
#include <QVariant>

class WeatherSettings;

class SettingsGroup : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name READ name CONSTANT)

public:
    explicit SettingsGroup(
        const QString& name, WeatherSettings* settings, QObject* parent = nullptr);
    virtual ~SettingsGroup() {}

    QString name() const { return m_name; }
    QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const;
    QVariant value(
        const QString& group, const QString& key, const QVariant& defaultValue = QVariant()) const;

    void setValue(const QString& key, const QVariant& value);
    void setValue(const QString& group, const QString& key, const QVariant& value);

signals:
    void settingsGroupUpdated();

protected:
    QString m_name;
    WeatherSettings* m_settings = nullptr;
};

#endif // SETTINGSGROUP_H
