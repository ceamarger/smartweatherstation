#include "locationfinder.h"

#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

LocationListModel LocationFinder::AvailableLocations;
CountryListModel LocationFinder::AvailableCountries;
const QString LocationFinder::CityListFilePath = "data/citylist.json";
const QString LocationFinder::CountryListFilePath = "data/countrylist.json";

LocationFinder::LocationFinder(QObject* parent)
    : QObject(parent)
{
    populateCountries();
    populateLocations();
}

void LocationFinder::populateCountries()
{
    QFile countryListFile(CountryListFilePath);

    if (!countryListFile.open(QFile::ReadOnly | QFile::Text | QIODevice::ExistingOnly)) {
        QFileInfo cityListFileInfo(countryListFile);
        qDebug() << countryListFile.errorString() << cityListFileInfo.absoluteFilePath();
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(countryListFile.readAll());
    QJsonArray countriesJsonArray = document.array();

    for (auto countriesJsonValueRef : countriesJsonArray) {
        auto countriesJson = countriesJsonValueRef.toObject();

        AvailableCountries.append(new Country(countriesJson[CountryJsonKeys::NumericCode].toInt(),
            countriesJson[CountryJsonKeys::Name].toString(),
            countriesJson[CountryJsonKeys::Alpha2Code].toString(),
            countriesJson[CountryJsonKeys::Alpha3Code].toString(),
            countriesJson[CountryJsonKeys::Region].toString(), this));
    }
}

void LocationFinder::populateLocations()
{
    QFile cityListFile(CityListFilePath);

    if (!cityListFile.open(QFile::ReadOnly | QFile::Text | QIODevice::ExistingOnly)) {
        QFileInfo cityListFileInfo(cityListFile);
        qDebug() << cityListFile.errorString() << cityListFileInfo.absoluteFilePath();
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(cityListFile.readAll());
    QJsonArray citiesJsonArray = document.array();

    for (auto citiesJsonValueRef : citiesJsonArray) {
        auto citiesJson = citiesJsonValueRef.toObject();
        auto citiesCoordJson = citiesJson[LocationJsonKeys::Coordinates].toObject();

        Coordinates coords;
        coords.latitude = citiesCoordJson[LocationJsonKeys::Latitude].toVariant().toReal();
        coords.longitude = citiesCoordJson[LocationJsonKeys::Longitude].toVariant().toReal();

        auto country = citiesJson[LocationJsonKeys::Country].toString();
        AvailableLocations.append(new Location(citiesJson[LocationJsonKeys::Id].toInt(),
            citiesJson[LocationJsonKeys::Name].toString(),
            citiesJson[LocationJsonKeys::State].toString(), country.isEmpty() ? "Other" : country,
            coords, this));
    }

    qDebug() << AvailableLocations.rowCount() << "cities imported.";
}

const Location* LocationFinder::fromLocationId(qint64 id) const
{
    return AvailableLocations.getFromId(id);
}
