import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0

import "components"
import "settingsMenus"

Window {
    id: mainAppWindow
    visible: true
    width: 840
    height: 480
    title: qsTr("Smart Weather Station")

    function hideSettings() {
        unblurBackgroundAnimation.start()
        settingsView.hide()
    }

    function showSettings() {
        blurBackgroundAnimation.start()
        settingsView.show()
    }

    MainScreenContent {
        id: mainContent
        anchors.fill: parent
    }

    Item {
        id: blurBackground
        anchors.fill: parent
        opacity: 0

        NumberAnimation {
            id: blurBackgroundAnimation
            target: blurBackground
            property: "opacity"
            to: 1.0
            duration: 200
        }

        NumberAnimation {
            id: unblurBackgroundAnimation
            target: blurBackground
            property: "opacity"
            to: 0.0
            duration: 200
        }

        ShaderEffectSource {
            id: effectSource
            sourceItem: mainContent
            anchors.fill: parent
            sourceRect: Qt.rect(blurBackground.x,blurBackground.y,blurBackground.width,blurBackground.height)
        }

        FastBlur{
            id: blur
            anchors.fill: effectSource
            source: effectSource
            radius: 30
        }
    }

    SettingsMenuContainer {
        id: settingsView
        anchors.fill: parent
        visible: false
    }

    Image {
        id: settings_menu_icon
        source: "/menus/settings_menu_icon.png"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 5
        opacity: 1

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
