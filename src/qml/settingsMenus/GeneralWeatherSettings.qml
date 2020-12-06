import QtQuick 2.15

import "../components"

SettingsMenu {
    id: root

    title: qsTr("General Weather")

    content: Item {
        anchors.fill: parent

        Column {
            width: parent.width

            Row {
                width: parent.width
                height: 30
                spacing: 10

                SWSText {
                    id: locationLabel
                    text: qsTr("Location :")
                    maxWidth: 150
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }

                SWSCombobox {
                    height: parent.height
                    width: parent.width - locationLabel.width - parent.spacing
                    model: locationFinder.availableLocations
                    textRole: "name"
                    editable: true
                }
            }
        }
    }
}
