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
    populateLocations();
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

        AvailableLocations.append(new Location(citiesJson[LocationJsonKeys::Id].toInt(),
            citiesJson[LocationJsonKeys::Name].toString(),
            citiesJson[LocationJsonKeys::State].toString(),
            citiesJson[LocationJsonKeys::Country].toString(), coords, this));
    }

    qDebug() << AvailableLocations.rowCount() << "cities imported.";
}

const Location* LocationFinder::fromLocationId(qint64 id) const
{
    return AvailableLocations.getFromId(id);
}
