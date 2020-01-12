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
    }

    SwitchableBlur {
        id: blurBackground
        sourceItem: mainContent
        animationDuration: 200
        radius: 40
        anchors.fill: parent
    }

    SettingsMenuContainer {
        id: settingsView
        anchors.fill: parent
        visible: false
    }

    Image {
        id: settings_menu_icon
        source: settingsView.visible ? "/menus/exit_settings_icon.png"
                                     : "/menus/settings_menu_icon.png"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 5

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (settingsView.visible)
                    hideSettings()
                else
                    showSettings()
            }
        }
    }
}
