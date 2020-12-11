#ifndef LOCATIONFINDER_H
#define LOCATIONFINDER_H

#include <QObject>

#include "countrylistmodel.h"
#include "locationlistmodel.h"

class LocationFinder : public QObject {
    Q_OBJECT

    Q_PROPERTY(CountryListModel* availableCountries READ availableCountries CONSTANT)
    Q_PROPERTY(LocationListModel* availableLocations READ availableLocations CONSTANT)

public:
    explicit LocationFinder(QObject* parent = nullptr);

    Q_INVOKABLE const Location* fromLocationId(qint64 id) const;

private:
    void populateCountries();
    void populateLocations();

private:
    CountryListModel* availableCountries() const { return &AvailableCountries; }
    LocationListModel* availableLocations() const { return &AvailableLocations; }

    // NOTE (camar) : countries json can be generated on https://restcountries.eu/
    static CountryListModel AvailableCountries;
    static LocationListModel AvailableLocations;
    static const QString CityListFilePath;
    static const QString CountryListFilePath;
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

namespace CountryJsonKeys {

static QString NumericCode = "numericCode";
static QString Name = "name";
static QString Alpha2Code = "alpha2Code";
static QString Alpha3Code = "alpha3Code";
static QString Region = "region";
}

#endif // LOCATIONFINDER_H
