import QtQuick 2.12

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
        color: "blue"
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
