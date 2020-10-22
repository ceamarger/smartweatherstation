import QtQuick 2.15
import QtQuick.Controls 2.15

TextField {
    id: root

    color: "white"
    font.family: "Helvetica"

    background: Rectangle {
        color: "#59ace3"
        border.color: parent.activeFocus ? "#7afffd" : "transparent"
    }
}
