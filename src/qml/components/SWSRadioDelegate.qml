import QtQuick 2.0

import QtQuick.Controls 2.15

RadioDelegate {
    id: control

    contentItem: SWSText {
        leftPadding: control.indicator.width + control.spacing
        width: control.width - control.indicator.width - control.spacing
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
    }

    indicator: Rectangle {
        implicitWidth: 26
        implicitHeight: 26
        x: 0
        y: parent.height / 2 - height / 2
        radius: 13
        color: "transparent"
        border.color: "black"

        Rectangle {
            width: 14
            height: 14
            x: 6
            y: 6
            radius: 7
            color: "black"
            visible: control.checked
        }
    }

    background: Rectangle {
        visible: false
    }
}
