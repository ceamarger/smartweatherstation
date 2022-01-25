import QtQuick 2.15

import "../components"

SettingsMenu {
    id: root

    title: qsTr("Sensors")

    content: Item {
        anchors.fill: parent

        QtObject {
            id: __private

            readonly property var indoorWeatherData: weather.data.indoorWeatherData
            readonly property var rooms: indoorWeatherData.rooms
            readonly property var mainRoom: indoorWeatherData.mainRoom
        }

        function updateMainRoom(uuid) {
            __private.indoorWeatherData.setMainRoomUuid(uuid)
        }

        Column {
            width: parent.width
            spacing: 10

            SWSText {
                id: noRoomsText
                text: "No rooms."
                visible: __private.rooms.rowCount() === 0
            }

            ListView {
                model: __private.rooms
                height: contentHeight
                contentHeight: childrenRect.height

                delegate: SWSRadioDelegate {
                    id: control

                    text: name
                    checked: uuid === __private.mainRoom.uuid

                    onCheckedChanged: if (checked) updateMainRoom(uuid)
                }
            }
        }
    }
}
