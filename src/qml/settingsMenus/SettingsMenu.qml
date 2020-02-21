import QtQuick 2.12

import "../components"

Item {
    id: root
    anchors.fill: parent

    property string title: ""

    property alias content : menuLoader.sourceComponent

    function show() {
        menuLoader.active = true
    }

    function hide() {
        menuLoader.active = false
    }

    Item {
        anchors.fill: parent

        MouseArea {
            id: focusMouseArea
            anchors.fill: parent
            onClicked: forceActiveFocus()
        }

        SWSText {
            id: titleText
            text: title
            font.bold: true
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
                margins: 10
            }
        }

        Rectangle {
            id: titleSeparator
            color: "black"
            height: 1
            anchors {
                top: titleText.bottom
                left: parent.left
                right: parent.right
                margins: 10
            }
        }

        Loader {
            id: menuLoader
            anchors {
                top: titleSeparator.bottom
                bottom: parent.bottom
                left: parent.left
                right: parent.right
                margins: 10
            }
            active: false
        }
    }
}
