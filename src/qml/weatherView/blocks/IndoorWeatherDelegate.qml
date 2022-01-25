import QtQuick 2.0

import "../../"
import "../../components"

import sws.utils 1.0

Column {
    id: root
    spacing: 10

    property bool roomHasTemperature: false
    property int roomTemperature
    property string roomName: ""
    property bool nameVisible: true

    readonly property alias roomNameTextItem: roomNameItem
    readonly property int reducedHeight: indoorTemperatureText.height
    readonly property int extendedHeight: indoorTemperatureText.height + roomNameTextItem.lineCount * roomNameTextItem.font.pixelSize + spacing

    QtObject {
        id: __private

        readonly property var temperatureSettings: weather.data.settings.temperatureSettings
        readonly property string noTemperatureString: " - "
    }

    SWSText {
        id: indoorTemperatureText
        text: {
            var convertedTemperatureString =
                    root.roomHasTemperature ? TemperatureConverter.convert(
                                         root.roomTemperature / 100,
                                         TemperatureConverter.Kelvin,
                                         TemperatureHelper.settingsUnitToConverterUnit(__private.temperatureSettings.unit)
                                         ).toFixed(1)
                                   : __private.noTemperatureString

            return convertedTemperatureString + __private.temperatureSettings.unitString
        }
        font.pixelSize: 25
        font.bold: true
        anchors.right: parent.right
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideNone
        wrapMode: Text.NoWrap
    }

    SWSText {
        id: roomNameItem
        property real maxOpacity: 0.8

        height: 17 * maximumLineCount // height needed in order to both wrap AND elide with the maximumLineCount property
        width: Math.max(parent.width, 100)
        anchors.right: parent.right

        text: root.roomName
        font.pixelSize: 12

        visible: opacity > .0
        opacity: nameVisible ? maxOpacity : 0.0

        wrapMode: Text.Wrap
        elide: Text.ElideRight
        maximumLineCount: 2
        horizontalAlignment: Text.AlignRight
    }
}
