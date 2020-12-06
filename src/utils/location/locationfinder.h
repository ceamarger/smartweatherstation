#ifndef LOCATIONFINDER_H
#define LOCATIONFINDER_H

#include <QObject>

struct Coordinates {
    qreal longitude;
    qreal latitude;
};

struct Location {
    qint64 id = -1;
    QString name = "";
    QString state = "";
    QString country = "";
    Coordinates coordinates = { .0, .0 };
};

class LocationFinder : public QObject {
    Q_OBJECT

public:
    explicit LocationFinder(QObject* parent = nullptr);

    void populateLocations();

private:
    static QList<Location> Locations;

    static const QString CityListFilePath;
};

namespace LocationJsonKeys {

static QString Id = "id";
static QString Name = "name";
static QString State = "state";
static QString Country = "country";
static QString Coordinates = "coord";
static QString Longitude = "lon";
static QString Latitude = "lat";
}

#endif // LOCATIONFINDER_H
