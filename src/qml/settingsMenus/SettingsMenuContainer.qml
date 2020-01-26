import QtQuick 2.12

import ".."
import "../components"

Item {
    id: root

    property int animationDuration: 0

    signal exitClicked()

    property list<SettingsMenu> menus: [
        SettingsMenu {
            title: "Weather API"

            Item {
                anchors.fill: parent

                SWSText {
                    text: "Weather API Menu"
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        },
        SettingsMenu {
            title: "Localization"
        }
    ]

    function show() {
        root.visible = true
        displaySettingsView()
    }

    function hide() {
        hideSettingsView()
    }

    function displaySettingsView() {
        hideMenuSelectorAnimation.stop()
        if (!displayMenuSelectorAnimation.running)
            displayMenuSelectorAnimation.start()

        hideExitIconAnimation.stop()
        if (!displayExitIconAnimation.running)
            displayExitIconAnimation.start()
    }

    function hideSettingsView() {
        displayMenuSelectorAnimation.stop()
        if (!hideMenuSelectorAnimation.running)
            hideMenuSelectorAnimation.start()

        displayExitIconAnimation.stop()
        if (!hideExitIconAnimation.running)
            hideExitIconAnimation.start()
    }

    function selectMenu(index) {
        selectedMenuContent.children.push(root.menus[index])
        root.menus[index].show()
    }

    function deselectMenu(index) {
        root.menus[index].hide()
        selectedMenuContent.removeChildMenu(root.menus[index])
    }

    MenuSelector {
        id: menuSelector
        menus: root.menus
        x: -width
        height: parent.height
        width: parent.width / (Constants.goldenRatio * 3)
        color: "#1ab5ed"

        NumberAnimation {
            id: displayMenuSelectorAnimation
            target: menuSelector
            property: "x"
            to: 0
            duration: root.animationDuration
            easing.type: Easing.OutSine
        }

        NumberAnimation {
            id: hideMenuSelectorAnimation
            property: "x"
            target: menuSelector
            to: -menuSelector.width
            duration: root.animationDuration
            easing.type: Easing.OutSine

            onStopped: root.visible = false
        }
    }

    Rectangle {
        id: selectedMenuContent
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: menuSelector.right
        width: menuSelector.hasSelectedMenu ? parent.width - menuSelector.width : 0
        clip: true
        color: "#0e6096"

        Behavior on width {
            NumberAnimation {
                id: displaySelectedMenuAnimation
                duration: root.animationDuration
                easing.type: Easing.OutSine
            }
        }

        function removeChildMenu(menu) {
            var childrenToKeep = []
            for (var i = 0 ; i < children.length ; ++i) {
                if (children[i] !== menu)
                    tmpChildren.push(children[i])
            }
            children = childrenToKeep
        }
    }

    Image {
        id: exitMenuIcon

        source: "/menus/exit_settings_icon.png"
        anchors.top: parent.top
        anchors.margins: 5

        x: root.width

        NumberAnimation {
            id: displayExitIconAnimation
            target: exitMenuIcon
            property: "x"
            to: root.width - exitMenuIcon.width - exitMenuIcon.anchors.margins
            duration: root.animationDuration
            easing.type: Easing.OutSine
        }

        NumberAnimation {
            id: hideExitIconAnimation
            property: "x"
            target: exitMenuIcon
            to: root.width
            duration: root.animationDuration
            easing.type: Easing.OutSine
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                menuSelector.resetSelection()
                root.exitClicked()
            }
        }
    }
}
