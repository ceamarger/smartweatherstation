pragma Singleton

import QtQuick 2.15

QtObject {
    id: constants

    readonly property int windowWidth: 840
    readonly property int windowHeight: 480

    readonly property real goldenRatio: 1.62
    readonly property int blurRadius: 40
    readonly property int displayAnimationDuration: goldenRatio * 1000 / 2
}
