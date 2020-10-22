import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root

    property int animationDuration: 0

    property alias sourceItem: effectSource.sourceItem
    property alias radius: blur.radius

    opacity: 0

    function blur() {
        unblurAnimation.stop()
        if (!blurAnimation.running)
            blurAnimation.start()
    }

    function unblur() {
        blurAnimation.stop()
        if (!unblurAnimation.running)
            unblurAnimation.start()
    }

    readonly property bool isActive: opacity > 0

    NumberAnimation {
        id: blurAnimation
        target: root
        property: "opacity"
        to: 1.0
        duration: root.animationDuration
    }

    NumberAnimation {
        id: unblurAnimation
        target: root
        property: "opacity"
        to: 0.0
        duration: root.animationDuration
    }

    ShaderEffectSource {
        id: effectSource
        anchors.fill: parent
        sourceRect: Qt.rect(root.x, root.y, root.width, root.height)
    }

    FastBlur{
        id: blur
        anchors.fill: effectSource
        source: effectSource
        radius: 0
    }

    // MouseArea used to block inputs behind the blur
    MouseArea {
        anchors.fill: parent
        enabled: root.isActive
    }
}
