import QtQuick 2.0
import QtQuick.Controls 2.15

Dialog {
    id: root

    property string uuid: ""

    QtObject {
        id: __private

        readonly property var indoorWeatherData: weather.data.indoorWeatherData
    }

    title: "Register new Room"

    standardButtons: Dialog.Ok | Dialog.Cancel
    onAccepted: __private.indoorWeatherData.registerRoom(uuid, roomNameField.text)
    onRejected: uuid = ""

    onOpened: reset()

    property Item acceptedButton: standardButton(Dialog.Ok)

    function reset() {
        acceptedButton.enabled = false
        roomNameField.text = ""
    }

    contentItem: Item {
        Column {
            spacing: 5

            Text {
                text: "ID : " + root.uuid
            }

            Row {
                spacing: 5
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Choose a name :"
                }
                TextField {
                    id: roomNameField
                    anchors.verticalCenter: parent.verticalCenter
                    placeholderText: "Room name..."

                    onTextEdited: acceptedButton.enabled = (text !== "")
                }
            }
        }

        Connections {
            target: __private.indoorWeatherData
            function onNewRoomReceived(uuid) {
                root.open()
                root.uuid = uuid
            }
        }
    }
}
