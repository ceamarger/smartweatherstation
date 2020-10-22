import QtQuick 2.0

import "../../components"

Item {
    id: root

    width: childrenRect.width
    height: childrenRect.height

    Row {
        id: indoorTemperatureRow
        spacing: 15

        SWSText {
            id: indoorTemperatureText
            text: "0°K"
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
