import QtQuick 2.12
import QtQuick.Controls 2.12

TextField {
    id: root

    color: "white"
    font.family: "Helvetica"

    background: Rectangle {
        color: "#59ace3"
        border.color: parent.activeFocus ? "#7afffd" : "transparent"
    }
}
