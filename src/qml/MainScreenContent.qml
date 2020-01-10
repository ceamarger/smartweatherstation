import QtQuick 2.12

import "components"

Rectangle {
    id: mainContent
    anchors.fill: parent

    Image {
        id: background
        source: "/backgrounds/mainBackground.jpg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        opacity: 0.3
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
