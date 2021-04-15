import QtQuick 2.15

import ".."
import "../components"
import "blocks"

Rectangle {
    id: root
    anchors.fill: parent

    signal settingsClicked()

    state : __private.simplifiedViewState

    QtObject {
        id: __private

        readonly property string simplifiedViewState: "simplifiedView"
        readonly property string completeViewState: "completeView"

        readonly property bool isCompleteView: root.state === completeViewState

        readonly property int defaultBorderMargin: 25
    }

    states: [
        State {
            name: __private.simplifiedViewState
            AnchorChanges {
                target: animationInvisibleItem
                anchors.top: undefined; anchors.verticalCenter: root.verticalCenter
            }
        },
        State {
            name: __private.completeViewState
            AnchorChanges {
                target: animationInvisibleItem
                anchors.top: root.top; anchors.verticalCenter: undefined
            }
        }
    ]

    transitions: Transition {
        AnchorAnimation {
            duration: Constants.displayAnimationDuration
            easing.type: Easing.OutSine
        }
    }

    function switchState() {
        switch (root.state) {
        case __private.simplifiedViewState:
            root.state = __private.completeViewState
            break
        default:
            root.state = __private.simplifiedViewState
        }
    }

    Image {
        id: background
        source: "/backgrounds/mainBackground.jpg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        opacity: 0.3
    }

    // Main Content
    DatetimeBlock {
        id: dateTimeBlock
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: animationInvisibleItem.verticalCenter
    }

    OutdoorWeatherBlock {
        id: outdoorWeatherBlock
        anchors.top: animationInvisibleItem.top
        anchors.left: parent.left
        anchors.leftMargin: __private.defaultBorderMargin

        reduced: !__private.isCompleteView
    }

    IndoorWeatherBlock {
        id: indoorWeatherBlock
        anchors.top: animationInvisibleItem.top
        anchors.right: parent.right
        anchors.rightMargin: __private.defaultBorderMargin

        reduced: !__private.isCompleteView
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.switchState()
    }

    Image {
        id: settingsMenuIcon
        source: "/menus/settings_menu_icon.png"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 5

        visible: __private.isCompleteView

        MouseArea {
            anchors.fill: parent
            onClicked: root.settingsClicked()
        }
    }

    /* Invisible item used to simplify the transition anchors animation
     * between simplified and complete view
     */
    Item {
        id: animationInvisibleItem
        height: outdoorWeatherBlock.minimalHeight
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        anchors.margins: __private.defaultBorderMargin
    }
}
