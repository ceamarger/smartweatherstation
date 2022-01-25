import QtQuick 2.15

import sws.utils 1.0

import "../../components"

Block {
    id: root

    QtObject {
        id: __private

        readonly property var generalWeatherSettings: weather.data.settings.generalWeatherSettings
    }

    Column {
        id: dateTimeColumn
        spacing: 15

        SWSText {
            id: locationText
            text: {
                var location = locationFinder.fromLocationId(__private.generalWeatherSettings.locationId)
                return location ? location.name : qsTr("Where are you ?")
            }
            font.pixelSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        SWSText {
            id: timeText
            text: dateTimeSettings.currentTime
            font.pixelSize: 25
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        SWSText {
            id: dateText
            text: dateTimeSettings.currentDate
            font.pixelSize: 15
            font.capitalization: Font.Capitalize
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
