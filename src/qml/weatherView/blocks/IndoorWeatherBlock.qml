import QtQuick 2.15

import "../../"
import "../../components"

import sws.utils 1.0

Block {
    id: root

    QtObject {
        id: __private

        readonly property var weatherData: weather.data
        readonly property var indoorWeatherData: weatherData.indoorWeatherData
        readonly property var mainRoom: indoorWeatherData.mainRoom

        readonly property var temperatureSettings: weather.data.settings.temperatureSettings

        readonly property string noTemperatureString: " - "
    }

    Column {
        id: indoorTemperatureColumn
        spacing: 10

        Row {
            id: indoorTemperatureRow
            spacing: 15

            SWSText {
                id: indoorTemperatureText
                text: {
                    var hasTemperature = __private.mainRoom && __private.mainRoom.hasTemperature
                    var convertedTemperatureString =
                            hasTemperature ? TemperatureConverter.convert(
                                                 __private.indoorWeatherData.mainRoom.temperature / 100,
                                                 TemperatureConverter.Kelvin,
                                                 TemperatureHelper.settingsUnitToConverterUnit(__private.temperatureSettings.unit)
                                                 ).toFixed(1)
                                           : __private.noTemperatureString

                    return convertedTemperatureString + __private.temperatureSettings.unitString
                }
                font.pixelSize: 25
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            Image {
                id: indoorWeatherImage
                source: "/weather/indoor_icon.png"
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Text {
            text: "+ " + qsTr("Touch to see all rooms")
            font.pixelSize: 9
            anchors.horizontalCenter: parent.horizontalCenter
            visible: opacity

            opacity: !reduced ? 0.6 : 0.0
            Behavior on opacity {
                NumberAnimation {
                    duration: Constants.displayAnimationDuration
                    easing.type: !root.reduced ? Easing.OutSine : Easing.InSine
                }
            }
        }
    }
}
