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

    Loader {
        id: menuLoader
        anchors.fill: parent
        active: false
    }
}
