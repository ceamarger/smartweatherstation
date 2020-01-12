import QtQuick 2.12

import "../components"

Item {
    id: root

    property int animationDuration: 1000 / (1.62*3)

    signal exitClicked()

    property list<Item> menus: [
        Item {
            property string title: "Weather API"
        },
        Item {
            property string title: "Localization"
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
        hideLeftSliderAnimation.stop()
        if (!displayLeftSliderAnimation.running)
            displayLeftSliderAnimation.start()

        hideExitIconAnimation.stop()
        if (!displayExitIconAnimation.running)
            displayExitIconAnimation.start()
    }

    function hideSettingsView() {
        displayLeftSliderAnimation.stop()
        if (!hideLeftSliderAnimation.running)
            hideLeftSliderAnimation.start()

        displayExitIconAnimation.stop()
        if (!hideExitIconAnimation.running)
            hideExitIconAnimation.start()
    }

    Rectangle {
        id: leftSlider
        x: -width
        height: parent.height
        width: parent.width / (1.62 * 3) // 1.62 match to the golden ratio (TODO : move this const to a specific constant file if needs to be reused)
        color: "#1ab5ed"

        SWSText {
            id: settingsTitle
            text: "Settings"
            width: parent.width
            font.pixelSize: 25
            font.bold: true
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                margins: 10
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            MouseArea {
                anchors.fill: parent
                onClicked: menusListView.currentIndex = -1
            }
        }

        ListView {
            id: menusListView
            width: parent.width
            anchors.top: settingsTitle.bottom
            anchors.bottom: parent.bottom
            anchors.topMargin: 10
            model: root.menus

            currentIndex: -1

            delegate: Rectangle {
                id: rootDelegate
                width: parent.width
                height: 50
                color: ListView.isCurrentItem ? "#0e6096" : "#1ab5ed"

                Rectangle {
                    id: separator
                    color: "black"
                    height: 1
                    anchors {
                        top: parent.top
                        left: parent.left
                        leftMargin: 10
                        right: parent.right
                        rightMargin: 10
                    }
                }

                SWSText {
                    text: title
                    anchors.fill: parent
                    font.pixelSize: 12
                    font.bold: rootDelegate.ListView.isCurrentItem
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: menusListView.currentIndex = index
                }
            }
        }

        NumberAnimation {
            id: displayLeftSliderAnimation
            target: leftSlider
            property: "x"
            to: 0
            duration: root.animationDuration
            easing.type: Easing.OutSine
        }

        NumberAnimation {
            id: hideLeftSliderAnimation
            property: "x"
            target: leftSlider
            to: -leftSlider.width
            duration: root.animationDuration
            easing.type: Easing.OutSine

            onStopped: root.visible = false
        }
    }

    Rectangle {
        id: selectedMenuContent
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: leftSlider.right
        width: menusListView.currentIndex === -1 ? 0 : parent.width - leftSlider.width
        color: "#0e6096"

        Behavior on width {
            NumberAnimation {
                id: displaySelectedMenuAnimation
                duration: root.animationDuration
                easing.type: Easing.OutSine
            }
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
                menusListView.currentIndex = -1
                root.exitClicked()
            }
        }
    }
}
