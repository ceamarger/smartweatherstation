#ifndef ABSTRACTWEATHERAPIACCESS_H
#define ABSTRACTWEATHERAPIACCESS_H

#include <QObject>
#include <QJsonDocument>

class AbstractWeatherAPIAccess : public QObject
{
    Q_OBJECT

public:
    explicit AbstractWeatherAPIAccess(QObject *parent = nullptr);

    virtual void requestData() = 0;

    QJsonDocument data() const { return m_data; }

signals:
    void dataUpdated(QJsonDocument data);

protected:
    void setData(QJsonDocument data);

private:
    QJsonDocument m_data;
};

#endif // ABSTRACTWEATHERAPIACCESS_H
