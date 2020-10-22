import QtQuick 2.15

import "../../components"

Item {
    id: root
    width: childrenRect.width
    height: childrenRect.height

    Column {
        id: dateTimeColumn
        spacing: 15

        SWSText {
            id: timeText
            text: dateTimeSettings.currentTime
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
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
