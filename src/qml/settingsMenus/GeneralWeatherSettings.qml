import QtQuick 2.15
import sws.utils 1.0
import SortFilterProxyModel 0.2

import "../components"

SettingsMenu {
    id: root

    title: qsTr("General Weather")

    content: Item {
        anchors.fill: parent

        QtObject {
            id: __private

            readonly property var generalWeatherSettings: weather.data.settings.generalWeatherSettings
        }

        SortFilterProxyModel {
            id: locationProxyModel
            sourceModel: locationFinder.availableLocations
            filters: RegExpFilter {
                roleName: "country"
                pattern: "^(?!.*Other).*$"
                caseSensitivity: Qt.CaseSensitive
            }
        }

        Column {
            width: parent.width
            spacing: 10

            Row {
                width: parent.width
                height: 30
                spacing: 10

                SWSText {
                    id: countryLabel
                    text: qsTr("Country :")
                    maxWidth: 150
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }

                SWSCombobox {
                    id: countryCombobox
                    height: parent.height
                    width: parent.width - locationLabel.width - parent.spacing
                    model: locationFinder.availableCountries
                    textRole: "name"
                    valueRole: "id"
                    editable: true
                }
            }

            SWSText {
                id: invalidCountryWarning
                text: qsTr("/!\ Uknown country. Please enter a valid one.")
                font.bold: true
                color: "darkred"
                visible: !countryCombobox.isValueValid
                verticalAlignment: Text.AlignVCenter
            }

            Row {
                width: parent.width
                height: 30
                spacing: 10

                SWSText {
                    id: locationLabel
                    text: qsTr("Location :")
                    maxWidth: 150
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }

                SWSCombobox {
                    id: locationCombobox
                    height: parent.height
                    width: parent.width - locationLabel.width - parent.spacing
                    model: locationProxyModel
                    textRole: "name"
                    valueRole: "id"
                    editable: true

                    Component.onCompleted: currentIndex = indexOfValue(__private.generalWeatherSettings.locationId)

                    onActivated: __private.generalWeatherSettings.locationId = model.get(index).id
                }
            }

            SWSText {
                id: invalidLocationWarning
                text: qsTr("/!\ Uknown city. Please enter a valid one.")
                font.bold: true
                color: "darkred"
                visible: !locationCombobox.isValueValid
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
