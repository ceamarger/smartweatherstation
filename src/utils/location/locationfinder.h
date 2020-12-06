#ifndef LOCATIONFINDER_H
#define LOCATIONFINDER_H

#include <QObject>

#include "locationlistmodel.h"

class LocationFinder : public QObject {
    Q_OBJECT

    Q_PROPERTY(LocationListModel* availableLocations READ availableLocations CONSTANT)

public:
    explicit LocationFinder(QObject* parent = nullptr);

    void populateLocations();

private:
    LocationListModel* availableLocations() const { return &AvailableLocations; }

    static LocationListModel AvailableLocations;
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
