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

    readonly property int maxSimulatorNumber: 6
    property int simulatorNumber: 1

    Row {
        id: simulatorsRow
        width: childrenRect.width

        SimulatorItem{}
    }

    Button {
        id: addSimulatorButton
        text: "+"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 5
        anchors.leftMargin: 5

        width: 20
        height: 20

        enabled: simulatorNumber < maxSimulatorNumber

        onClicked: {
            var component = Qt.createComponent("SimulatorItem.qml");
            var simulatorSprite = component.createObject(simulatorsRow);

            if (simulatorSprite === null)
                console.log("Error creating object");
            else
                simulatorNumber++
        }
    }

    Text {
        text: simulatorNumber + "/" + maxSimulatorNumber
        font.pixelSize: 10
        anchors.verticalCenter: addSimulatorButton.verticalCenter
        anchors.left: addSimulatorButton.right
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
    }
}
