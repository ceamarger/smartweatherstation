import QtQuick 2.15

import "../../components"

Item {
    id: root

    width: childrenRect.width
    height: childrenRect.height

    QtObject {
        id: __private

        readonly property var weatherData: weather.data
    }

    Row {
        id: indoorTemperatureRow
        spacing: 15

        SWSText {
            id: indoorTemperatureText
            text: (__private.weatherData.indoorTemperature / 100 )+ "°K"
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
