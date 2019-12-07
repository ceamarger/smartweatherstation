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
        spacing: 5

        SWSText {
            id: timeText
            text: "14h51"
            font.pixelSize: 25
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        SWSText {
            id: dateText
            text: dateTimeSettings.currentDate
            font.pixelSize: 15
            font.capitalization: Font.Capitalize
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
