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

    QSettings* settings() const { return m_settings; }

signals:
    void dataUpdated(QJsonDocument data);

protected:
    void setSettings(QSettings* settings);

private:
    QSettings *m_settings = nullptr;
};

#endif // ABSTRACTWEATHERAPIACCESS_H
