import QtQuick 2.12
import QtQuick.Window 2.12

import "components"
import "settingsMenus"

Window {
    id: mainAppWindow
    visible: true
    width: 840
    height: 480
    title: qsTr("Smart Weather Station")

    function hideSettings() {
        blurBackground.unblur()
        settingsView.hide()
    }

    function showSettings() {
        blurBackground.blur()
        settingsView.show()
    }

    MainScreenContent {
        id: mainContent
        anchors.fill: parent
        onSettingsClicked: showSettings()
    }

    SwitchableBlur {
        id: blurBackground
        sourceItem: mainContent
        animationDuration: 1000 / (1.62*3)
        radius: 40
        anchors.fill: parent
    }

    SettingsMenuContainer {
        id: settingsView
        anchors.fill: parent
        visible: false
        onExitClicked: hideSettings()
        animationDuration: 1000 / (1.62*3)
    }
}
