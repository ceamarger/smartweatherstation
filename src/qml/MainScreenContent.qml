import QtQuick 2.12

import "components"

Rectangle {
    id: root
    anchors.fill: parent

    signal settingsClicked()

    readonly property var weatherData: weather.data

    Component.onCompleted: root.state = __private.simplifiedViewState

    QtObject {
        id: __private

        readonly property string simplifiedViewState: "simplifiedView"
        readonly property string completeViewState: "completeView"

        readonly property bool isCompleteView: root.state === completeViewState

        readonly property int defaultBorderMargin: 25
    }

    states: [
        State {
            name: __private.simplifiedViewState
            AnchorChanges {
                target: animationInvisibleItem
                anchors.top: undefined; anchors.verticalCenter: root.verticalCenter
            }
        },
        State {
            name: __private.completeViewState
            AnchorChanges {
                target: animationInvisibleItem
                anchors.top: root.top; anchors.verticalCenter: undefined
            }
        }
    ]

    transitions: Transition {
        AnchorAnimation {
            duration: Constants.displayAnimationDuration
            easing.type: Easing.OutSine
        }
    }

    function switchState() {
        switch (root.state) {
        case __private.simplifiedViewState:
            root.state = __private.completeViewState
            break
        default:
            root.state = __private.simplifiedViewState
        }
    }

    Image {
        id: background
        source: "/backgrounds/mainBackground.jpg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        opacity: 0.3
    }

    // Main Content
    Column {
        id: dateTimeColumn
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: animationInvisibleItem.verticalCenter
        spacing: 15

        SWSText {
            id: timeText
            text: dateTimeSettings.currentTime
            font.pixelSize: 25
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        SWSText {
            id: dateText
            text: dateTimeSettings.currentDate
            font.pixelSize: 15
            font.capitalization: Font.Capitalize
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Column {
        id: outdoorWeatherColumn
        anchors.top: animationInvisibleItem.top
        anchors.left: parent.left
        anchors.leftMargin: __private.defaultBorderMargin
        spacing: 15

        Row {
            id: outdoorTemperatureRow
            spacing: 15

            Image {
                id: outdoorWeatherImage
                source: "/weather/cloud.png"
                anchors.verticalCenter: parent.verticalCenter
            }

            SWSText {
                id: outdoorTemperatureText
                text: (weatherData.outdoorTemperature / 100) + "°K"
                font.pixelSize: 25
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Item {
            id: sunEventsItem
            width: outdoorTemperatureRow.width
            height: childrenRect.height

            visible: __private.isCompleteView

            Row {
                id: sunriseRow
                anchors.left: parent.left
                spacing: 10

                Image {
                    id: sunriseIcon
                    source: "/weather/sunrise_icon.png"
                    anchors.verticalCenter: parent.verticalCenter
                }

                SWSText {
                    id: sunriseTimeText
                    text: Qt.formatTime(weatherData.sunriseTime)
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Row {
                id: sunsetRow
                anchors.right: parent.right
                spacing: 10

                visible: __private.isCompleteView

                Image {
                    id: sunsetIcon
                    source: "/weather/sunset_icon.png"
                    anchors.verticalCenter: parent.verticalCenter
                }

                SWSText {
                    id: sunsetTimeText
                    text: Qt.formatTime(weatherData.sunsetTime)
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        Row {
            id: humidityRow
            anchors.left: parent.left
            spacing: 10

            visible: __private.isCompleteView

            Image {
                id: humidityIcon
                source: "/weather/humidity_icon.png"
                anchors.verticalCenter: parent.verticalCenter
            }

            SWSText {
                id: humidityText
                text: weatherData.humidityPercentage + "%"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.switchState()
    }

    Image {
        id: settingsMenuIcon
        source: "/menus/settings_menu_icon.png"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 5

        visible: __private.isCompleteView

        MouseArea {
            anchors.fill: parent
            onClicked: root.settingsClicked()
        }
    }

    /* Invisible item used to simplify the transition anchors animation
     * between simplified and complete view
     */
    Item {
        id: animationInvisibleItem
        height: outdoorTemperatureRow.height
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        anchors.margins: __private.defaultBorderMargin
    }
}
