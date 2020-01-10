import QtQuick 2.12
import QtQuick.Window 2.12

import "components"

Window {
    visible: true
    width: 840
    height: 480
    title: qsTr("Smart Weather Station")

    Image {
        id: settings_menu_icon
        source: "/menus/settings_menu_icon.png"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 5
        opacity: 0.5

        MouseArea {
            anchors.fill: parent
            onClicked: console.log("Not implemented yet")
        }
    }

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
        spacing: 15

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
                text: (weatherData.outdoorTemperature / 100) + "°K"
                font.pixelSize: 25
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Item {
            id: sunEventsItem
            width: outdoorTemperatureRow.width
            height: childrenRect.height

            Row {
                id: sunriseRow
                anchors.left: parent.left
                spacing: 10

                Image {
                    id: sunriseIcon
                    source: "/weather/sunrise_icon.png"
                    anchors.verticalCenter: parent.verticalCenter
                }

                SWSText {
                    id: sunriseTimeText
                    text: Qt.formatTime(weatherData.sunriseTime)
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Row {
                id: sunsetRow
                anchors.right: parent.right
                spacing: 10

                Image {
                    id: sunsetIcon
                    source: "/weather/sunset_icon.png"
                    anchors.verticalCenter: parent.verticalCenter
                }

                SWSText {
                    id: sunsetTimeText
                    text: Qt.formatTime(weatherData.sunsetTime)
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        Row {
            id: humidityRow
            anchors.left: parent.left
            spacing: 10

            Image {
                id: humidityIcon
                source: "/weather/humidity_icon.png"
                anchors.verticalCenter: parent.verticalCenter
            }

            SWSText {
                id: humidityText
                text: weatherData.humidityPercentage + "%"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
