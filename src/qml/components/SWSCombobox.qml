import QtQuick 2.15
import QtQuick.Controls 2.15

ComboBox {
    id: root

    background: Rectangle {
        border.color: parent.activeFocus ? "#7afffd" : "transparent"
        color: "#59ace3"
    }

    delegate: ItemDelegate {
        width: root.width
        contentItem: Text {
            text: modelData
            color: "black"
            font.family: "Helvetica"
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        highlighted: root.highlightedIndex === index
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
