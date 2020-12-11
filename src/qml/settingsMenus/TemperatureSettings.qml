import QtQuick 2.15

import "../components"

SettingsMenu {
    id: root

    title: qsTr("Temperature")

    content: Item {
        anchors.fill: parent

        QtObject {
            id: __private

            readonly property var temperatureSettings: weather.data.settings.temperatureSettings
        }

        Column {
            width: parent.width

            Row {
                width: parent.width
                height: 30
                spacing: 10

                SWSText {
                    id: temperatureUnitLabel
                    text: qsTr("Unit :")
                    maxWidth: 150
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }

                SWSCombobox {
                    height: parent.height
                    width: parent.width - temperatureUnitLabel.width - parent.spacing
                    model: __private.temperatureSettings.availableUnitsStrings

                    Component.onCompleted: currentIndex = __private.temperatureSettings.unit
                    onActivated: __private.temperatureSettings.unit = __private.temperatureSettings.availableUnitAtIndex(index)
                }
            }
        }
    }
}
