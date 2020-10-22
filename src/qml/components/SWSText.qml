import QtQuick 2.15

Text {
    id: root

    property int maxWidth: parent.width

    readonly property alias boundingRect: swsTextMetrics.tightBoundingRect

    width: maxWidth > 0 ? Math.min(boundingRect.width, maxWidth) : boundingRect.width
    height: boundingRect.height

    font.family: "Helvetica"
    wrapMode: boundingRect.width > maxWidth ? Text.Wrap : Text.NoWrap
    elide: boundingRect.width > maxWidth ? Text.ElideRight : Text.ElideNone

    TextMetrics {
        id: swsTextMetrics
        font: root.font
        text: root.text
    }
}
