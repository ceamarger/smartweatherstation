#ifndef ABSTRACTWEATHERAPIACCESS_H
#define ABSTRACTWEATHERAPIACCESS_H

#include <QObject>
#include <QJsonDocument>
#include <QSettings>

class AbstractWeatherAPIAccess : public QObject
{
    Q_OBJECT

public:
    explicit AbstractWeatherAPIAccess(QObject *parent = nullptr);

    virtual void requestData() = 0;

    QJsonDocument data() const { return m_data; }
    QSettings* settings() const { return m_settings; }

signals:
    void dataUpdated(QJsonDocument data);

protected:
    void setData(QJsonDocument data);
    void setSettings(QSettings* settings);

private:
    QJsonDocument m_data;
    QSettings *m_settings = nullptr;
};

#endif // ABSTRACTWEATHERAPIACCESS_H
