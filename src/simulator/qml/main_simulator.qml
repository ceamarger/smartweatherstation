import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import sensorSimulator 1.0

Window {
    id: mainAppWindow
    visible: true

    width: simulatorsRow.width
    height: simulatorsRow.height

    color: "grey"

    property int simulatorNumber: 1

    Row {
        id: simulatorsRow
        width: childrenRect.width

        Repeater {
            model: simulatorNumber
            delegate: SimulatorItem {}
        }
    }

    Button {
        text: "+"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 5
        anchors.leftMargin: 5

        width: 20
        height: 20

        enabled: simulatorNumber < 5

        onClicked: simulatorNumber++
    }
}
