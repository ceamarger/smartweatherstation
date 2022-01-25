import QtQuick 2.15
import QtQuick.Controls 2.15

import sensorSimulator 1.0

Item {
    id: root

    width: 200
    height: 350

    readonly property string offState: "off"
    readonly property string onState: "on"
    readonly property string connectingState: "connecting"
    readonly property string connectedState: "connected"
    states: [
        State { name: offState },
        State { name: onState },
        State { name: connectingState },
        State { name: connectedState }
    ]
    state: offState

    readonly property bool simulatorOn: state !== offState

    property string uuid: ""
    property real celsiusTemperature: 0

    property alias uuidMessage: uuidText.text

    function switchSimulatorOnOff() {
        switch (root.state) {
        case offState:
            if (uuid)
                root.state = root.connectedState
            else
                root.state = root.onState
            break;
        default:
            root.state = root.offState
        }
    }

    function generateUUID() {
        root.state = root.connectingState
        scriptLauncher.generateUUID()
    }

    function incrementTemperature(facteur = 1) {
        celsiusTemperature += .1 * facteur
    }

    function decrementTemperature(facteur = 1) {
        celsiusTemperature -= .1 * facteur
    }

    function sendTemperature() {
        var kelvinTemperature = (celsiusTemperature + 273.15) * 100
        scriptLauncher.sendSetTemperatureCommand(uuid, kelvinTemperature)
    }

    onCelsiusTemperatureChanged: sendTemperature()

    Connections {
        target: scriptLauncher
        function onScriptStarted() {
            if (uuid !== "" || root.state !== root.connectingState)
                return

            if (scriptLauncher.lastScriptLaunched === ScriptLauncher.UUIDGeneration)
                uuidMessage = "Waiting for UUID..."
        }

        function onUuidGenerationFinished(generatedUUID) {
            if (uuid !== ""  || root.state !== root.connectingState)
                return

            uuid = generatedUUID
            uuidMessage = "UUID: " + uuid
            if (uuid) {
                root.state = root.connectedState
                scriptLauncher.sendRegisterCommand(generatedUUID)
            }
        }

        function onScriptFailed(scriptType) {
            if (scriptType === ScriptLauncher.UUIDGeneration)
                uuidMessage = "UUID gen failed. Retry to connect."
        }
    }

    Rectangle {
        id: screen
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
        height: 50
        color: enabled ? "lightblue" : "black"

        enabled: root.simulatorOn
        onEnabledChanged: if (enabled && !uuid) uuidMessage = "No UUID. Please push \"Connect\"."

        Text {
            id: uuidText
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                margins: 3
            }
            height: parent.height / 4
            wrapMode: Text.WrapAnywhere
            font.pixelSize: 10
            visible: parent.enabled
        }

        Text {
            text: celsiusTemperature.toFixed(1) + "°C"
            anchors.top: uuidText.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 3
            font.pixelSize: 30
            visible: parent.enabled && root.state === connectedState
            verticalAlignment: Text.AlignVCenter
        }
    }

    RoundButton {
        id: onOffButton
        text: root.simulatorOn ? "Off" : "On"
        width: 30
        height: 30

        palette {
            button: root.simulatorOn ? "red" : "green"
        }

        anchors.top: screen.bottom
        anchors.left: parent.left
        anchors.margins: 10

        contentItem: Text {
                text: onOffButton.text
                font.pixelSize: 10
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

        onClicked: switchSimulatorOnOff()
    }

    Button {
        id: connectButton
        text: "Connect"
        anchors.top: onOffButton.bottom
        anchors.left: parent.left
        anchors.margins: 10

        enabled: root.state === root.onState

        onClicked: generateUUID()
    }

    Rectangle {
        anchors.top: connectButton.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10

        height: temperatureButtons.height + 10

        enabled: root.state === root.connectedState

        color: "transparent"
        border.color: "black"
        radius: 5

        Column {
            id: temperatureButtons
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter
            spacing: 5

            Text {
                text: qsTr("Temperature")
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }

            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    text: "0.1"
                    width: 30
                    font.pixelSize: 10
                    horizontalAlignment: Text.AlignHCenter
                }

                Text {
                    text: "1"
                    width: 30
                    font.pixelSize: 10
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    id: incrementTemperatureButton
                    text: "+"
                    width: 30
                    height: 30
                    font.pixelSize: 10

                    onClicked: incrementTemperature()
                }

                Button {
                    id: incrementTemperatureButton10
                    text: "++"
                    width: 30
                    height: 30
                    font.pixelSize: 10

                    onClicked: incrementTemperature(10)
                }
            }

            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    id: decrementTemperatureButton
                    text: "-"
                    width: 30
                    height: 30
                    font.pixelSize: 10

                    onClicked: decrementTemperature()
                }

                Button {
                    id: decrementTemperatureButton10
                    text: "--"
                    width: 30
                    height: 30
                    font.pixelSize: 10

                    onClicked: decrementTemperature(10)
                }
            }
        }
    }
}
