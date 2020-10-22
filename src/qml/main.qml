import QtQuick 2.12
import QtQuick.Window 2.12

import "components"
import "weatherView"
import "settingsMenus"

Window {
    id: mainAppWindow
    visible: true
    width: Constants.windowWidth
    height: Constants.windowHeight

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
        anchors.fill: parent
        sourceItem: mainContent
        animationDuration: Constants.displayAnimationDuration
        radius: Constants.blurRadius
    }

    SettingsMenuContainer {
        id: settingsView
        anchors.fill: parent
        animationDuration: Constants.displayAnimationDuration
        visible: false

        onExitClicked: hideSettings()
    }
}
