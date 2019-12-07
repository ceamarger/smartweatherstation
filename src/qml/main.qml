import QtQuick 2.12
import QtQuick.Window 2.12

import "components"

Window {
    visible: true
    width: 840
    height: 480
    title: qsTr("Smart Weather Station")

    Column {
        id: dateTimeItem
        anchors.centerIn: parent

        SWSText {
            id: timeText
            text: "14h51"
            font.pixelSize: 25
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
