import QtQuick 2.15
import QtQuick.Controls 2.15

ComboBox {
    id: root

    readonly property bool isValueValid: find(editText) !== -1

    background: Rectangle {
        border.color: parent.activeFocus ? "#7afffd" : "transparent"
        color: "#59ace3"
    }

    delegate: ItemDelegate {
        width: root.width
        contentItem: Text {
            text: root.textRole ? (Array.isArray(root.model) ? modelData[root.textRole]
                                                             : model[root.textRole])
                                : modelData
            color: "black"
            font.family: "Helvetica"
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        highlighted: root.highlightedIndex === index
    }

    contentItem: TextField {
        enabled: root.editable
        leftPadding: 0
        rightPadding: root.indicator.width + root.spacing

        text: root.editText
        color: root.isValueValid ? "black" : "red"
        font.family: "Helvetica"

        background: Rectangle {
            border.color: root.activeFocus ? (root.isValueValid ? "#7afffd" : "red")
                                           : "transparent"
            color: "#59ace3"
        }

        verticalAlignment: Text.AlignVCenter
    }

    popup: Popup {
        y: root.height - 1
        width: root.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: root.popup.visible ? root.delegateModel : null
            currentIndex: root.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            color: "#59ace3"
            radius: 2
        }
    }
}
