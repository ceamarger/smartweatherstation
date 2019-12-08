import QtQuick 2.12
import QtQuick.Window 2.12

import "components"

Window {
    visible: true
    width: 840
    height: 480
    title: qsTr("Smart Weather Station")

    Column {
        id: dateTimeColumn
        anchors.centerIn: parent
        spacing: 5

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

    Column {
        id: outdoorWeatherColumn
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 25
        spacing: 5

        Row {
            id: outdoorTemperatureRow
            spacing: 15

            Image {
                id: outdoorWeatherImage
                source: "/weather/cloud.png"
                anchors.verticalCenter: parent.verticalCenter
            }

            SWSText {
                id: outdoorTemperatureText
                text: "15°C"
                font.pixelSize: 25
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
