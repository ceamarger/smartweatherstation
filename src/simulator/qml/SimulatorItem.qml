import QtQuick 2.15
import QtQuick.Controls 2.15

import sensorSimulator 1.0

Item {
    id: root

    width: 200
    height: 350

    property bool simulatorOn: false
    readonly property bool connected: uuid

    property string uuid: ""
    property real celsiusTemperature: 0

    property alias uuidMessage: uuidText.text

    function switchSimulatorOnOff() {
        simulatorOn = !simulatorOn
        uuid = ""
        console.log("simulator : " + (simulatorOn ? "ON" : "OFF"))
    }

    function generateUUID() {
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
            if (uuid !== "")
                return

            if (scriptLauncher.lastScriptLaunched === ScriptLauncher.UUIDGeneration)
                uuidMessage = "Waiting for UUID..."
        }

        function onUuidGenerationFinished(generatedUUID) {
            if (uuid !== "")
                return

            uuid = generatedUUID
            uuidMessage = "UUID: " + uuid
            if (uuid)
                scriptLauncher.sendRegisterCommand(generatedUUID)
        }

        function onRegisterCommandFinished(output) {
            console.log(output)
            sendTemperature()
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
        anchors.margins: 5
        height: 50
        color: enabled ? "blue" : "black"

        enabled: simulatorOn
        onEnabledChanged: if (enabled) uuidMessage = "No UUID. Please push \"Connect\"."

        Text {
            id: uuidText
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                margins: 3
            }
            height: parent.height / 4
            elide: Text.ElideRight
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
            visible: parent.enabled && connected
            verticalAlignment: Text.AlignVCenter
        }
    }

    RoundButton {
        id: onOffButton
        text: simulatorOn ? "Off" : "On"
        width: 30
        height: 30
        palette.button: simulatorOn ? "red" : "green"

        anchors.top: screen.bottom
        anchors.left: parent.left
        anchors.margins: 5

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
        anchors.margins: 5

        enabled: simulatorOn && !connected

        onClicked: generateUUID()
    }

    Rectangle {
        anchors.top: connectButton.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5

        height: temperatureButtons.height + 10

        enabled: connected

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
