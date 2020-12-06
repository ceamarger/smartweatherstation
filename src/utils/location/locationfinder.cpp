#include "locationfinder.h"

#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

LocationListModel LocationFinder::AvailableLocations;
const QString LocationFinder::CityListFilePath = "data/citylist.json";

LocationFinder::LocationFinder(QObject* parent)
    : QObject(parent)
{
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

        Location location;
        location.id = citiesJson[LocationJsonKeys::Id].toInt();
        location.name = citiesJson[LocationJsonKeys::Name].toString();
        location.state = citiesJson[LocationJsonKeys::State].toString();
        location.country = citiesJson[LocationJsonKeys::Country].toString();
        location.coordinates = coords;

        AvailableLocations.append(location);
    }

    qDebug() << AvailableLocations.rowCount() << "cities imported.";
}
