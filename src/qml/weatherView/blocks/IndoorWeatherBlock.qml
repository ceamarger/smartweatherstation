import QtQuick 2.15

import "../../"
import "../../components"

import sws.utils 1.0

Block {
    id: root

    QtObject {
        id: __private

        readonly property var weatherData: weather.data
        readonly property var indoorWeatherData: weatherData.indoorWeatherData
        readonly property var mainRoom: indoorWeatherData.mainRoom

        readonly property var temperatureSettings: weather.data.settings.temperatureSettings

        readonly property string noTemperatureString: " - "
    }

    onReducedChanged: {
        if (reduced) reduceAnimation.start()
        else enhanceAnimation.start()
    }

    // Animations are made sequentialy instead of parallel when using "Behavior" component,
    // so this is why we have those "ParallelAnimation" components
    ParallelAnimation {
        id: reduceAnimation
        NumberAnimation {
            target: mainRoomDelegate.roomNameTextItem
            duration: Constants.displayAnimationDuration
            property: "opacity"
            to: 0
            easing.type: Easing.InSine
        }

        NumberAnimation {
            target: mainRoomDelegate
            duration: Constants.displayAnimationDuration
            property: "height"
            to: mainRoomDelegate.reducedHeight
            easing.type: Easing.InSine
        }
    }

    ParallelAnimation {
        id: enhanceAnimation
        NumberAnimation {
            target: mainRoomDelegate.roomNameTextItem
            duration: Constants.displayAnimationDuration
            property: "opacity"
            to: mainRoomDelegate.roomNameTextItem.maxOpacity
            easing.type: Easing.OutSine
        }
        NumberAnimation {
            target: mainRoomDelegate
            duration: Constants.displayAnimationDuration
            property: "height"
            to: mainRoomDelegate.extendedHeight
            easing.type: Easing.OutSine
        }
    }

    Column {
        id: indoorTemperatureColumn
        spacing: 20

        Row {
            id: indoorTemperatureRow
            height: indoorWeatherImage.height
            spacing: 15

            IndoorWeatherDelegate {
                id: mainRoomDelegate

                property var room: __private.mainRoom

                anchors.verticalCenter: parent.verticalCenter

                roomHasTemperature: room && room.hasTemperature
                roomTemperature: room ? room.temperature : 0
                roomName: room ? room.name : ""
                nameVisible: !reduced
            }

            Image {
                id: indoorWeatherImage
                source: "/weather/indoor_icon.png"
            }
        }

        Repeater {
            model: __private.indoorWeatherData.rooms
            delegate: IndoorWeatherDelegate {
                id: secondaryRoomDelegate

                roomHasTemperature: hasTemperature
                roomTemperature: temperature
                roomName: name
                nameVisible: !reduced

                property real maxOpacity: 0.8

                visible: opacity > .0 && __private.mainRoom && uuid !== __private.mainRoom.uuid
                opacity: !reduced ? maxOpacity : 0.0

                anchors.right: indoorTemperatureRow.right
                anchors.left: indoorTemperatureRow.left
                anchors.rightMargin: 10

                roomNameTextItem.maximumLineCount: 1

                Behavior on opacity {
                    NumberAnimation {
                        duration: Constants.displayAnimationDuration
                        easing.type: !root.reduced ? Easing.OutSine : Easing.InSine
                    }
                }
            }
        }
    }
}
