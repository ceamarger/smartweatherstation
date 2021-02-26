import QtQuick 2.15

import "../../"
import "../../components"

import sws.utils 1.0

Item {
    id: root

    width: childrenRect.width
    height: childrenRect.height

    QtObject {
        id: __private

        readonly property var weatherData: weather.data
        readonly property var indoorWeatherData: weatherData.indoorWeatherData
        readonly property var mainRoom: indoorWeatherData.mainRoom

        readonly property var temperatureSettings: weather.data.settings.temperatureSettings

        readonly property string noTemperatureString: " - "
    }

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
}
