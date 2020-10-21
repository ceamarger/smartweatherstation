import QtQuick 2.0

import "../../components"

Item {
    id: root
    width: childrenRect.width
    height: childrenRect.height

    readonly property int minimalHeight: outdoorTemperatureRow.height

    property alias sunEventsInfoVisible: sunEventsItem.visible
    property alias humidityInfoVIsible: humidityRow.visible

    QtObject {
        id: __private

        readonly property var weatherData: weather.data
    }

    Column {
        id: outdoorWeatherColumn
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
                text: (__private.weatherData.outdoorTemperature / 100) + "°K"
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
                    text: Qt.formatTime(__private.weatherData.sunriseTime)
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
                    text: Qt.formatTime(__private.weatherData.sunsetTime)
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
                text: __private.weatherData.humidityPercentage + "%"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
