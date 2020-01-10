import QtQuick 2.12

import "../components"

Item {
    id: root

    function show() {
        root.visible = true
        displayLeftSlider()
    }

    function hide() {
        hideLeftSlider()
    }

    function displayLeftSlider() {
        hideLeftSliderAnimation.stop()
        if (!displayLeftSliderAnimation.running)
            displayLeftSliderAnimation.start()
    }

    function hideLeftSlider() {
        displayLeftSliderAnimation.stop()
        if (!hideLeftSliderAnimation.running)
            hideLeftSliderAnimation.start()
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
        }

        Rectangle {
            id: separator
            color: "black"
            height: 1
            anchors {
                top: settingsTitle.bottom
                left: parent.left
                right: parent.right
                margins: 10
            }
        }
    }

    NumberAnimation {
        id: displayLeftSliderAnimation
        target: leftSlider
        property: "x"
        to: 0
        duration: 250
        easing.type: Easing.OutSine
    }

    NumberAnimation {
        id: hideLeftSliderAnimation
        property: "x"
        target: leftSlider
        to: -leftSlider.width
        duration: 250
        onStopped: root.visible = false
        easing.type: Easing.OutSine
    }
}
