import QtQuick 2.12

import ".."
import "../../components"

SettingsMenu {
    id: root

    title: qsTr("Open Weather Map API")

    content: Item {
        anchors.fill: parent

        Row {
            width: parent.width
            height: 30
            spacing: 10

            SWSText {
                id: appIdLabel
                text: qsTr("App ID :")
                maxWidth: 150
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            SWSTextField {
                height: parent.height
                width: parent.width - appIdLabel.width - parent.spacing
                text: weather.data.api.appId
            }
        }
    }
}
