import QtQuick 2.12

import ".."
import "../components"

Rectangle {
    id: root

    property list<SettingsMenu> menus

    readonly property int currentMenuIndex: menusListView.currentIndex
    readonly property bool hasSelectedMenu: currentMenuIndex !== -1

    function resetSelection() {
        menusListView.currentIndex = -1
    }

    SWSText {
        id: settingsTitle
        text: qsTr("Settings")
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
            onClicked: resetSelection()
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

            readonly property var contentData: model
            readonly property int isCurrentItem: ListView.isCurrentItem

            width: parent.width
            height: 50
            color: isCurrentItem ? Colors.darkBlue1 : Colors.lightBlue1

            onIsCurrentItemChanged: {
                if (!isCurrentItem)
                    deselectMenu(index)
                else
                    selectMenu(index)
            }

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
                font.bold: rootDelegate.isCurrentItem
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: menusListView.currentIndex = index
            }
        }
    }
}
