import QtQuick 2.12

import "../../components"

SettingsMenu {
    id: root

    title: qsTr("Open Weather Map API")

    Item {
        anchors.fill: parent

        SWSText {
            text: root.title
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
