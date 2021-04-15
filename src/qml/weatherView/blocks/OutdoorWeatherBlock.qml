import QtQuick 2.15

import "../.."
import "../../components"

import sws.utils 1.0

Block {
    id: root

    readonly property int minimalHeight: outdoorTemperatureRow.height

    QtObject {
        id: __private

        readonly property var weatherData: weather.data
        readonly property var temperatureSettings: weather.data.settings.temperatureSettings
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
                text: TemperatureConverter.convert(__private.weatherData.outdoorTemperature / 100,
                                                   TemperatureConverter.Kelvin,
                                                   TemperatureHelper.settingsUnitToConverterUnit(__private.temperatureSettings.unit)).toFixed(1)
                      + __private.temperatureSettings.unitString
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
            visible: opacity

            opacity: !reduced ? 1.0 : 0.0
            Behavior on opacity {
                NumberAnimation {
                    duration: Constants.displayAnimationDuration
                    easing.type: !root.reduced ? Easing.OutSine : Easing.InSine
                }
            }

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
            visible: opacity

            opacity: !reduced ? 1.0 : 0.0
            Behavior on opacity {
                NumberAnimation {
                    duration: Constants.displayAnimationDuration
                    easing.type: !root.reduced ? Easing.OutSine : Easing.InSine
                }
            }

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
