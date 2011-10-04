import QtQuick 1.0

Component {
    Item {
        id: root
        width: parent.width
        height: 30

        SystemPalette {
            id: pal
        }

        Rectangle {
            id: background
            anchors.fill: parent
            color: pal.alternateBase
            opacity: index % 2 ? 1 : 0
        }

        Image {
            id: image
            anchors.verticalCenterOffset: 0
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            sourceSize.height: 22
            sourceSize.width: 22
            source: "images/note.svgz"

        }

        Text {
            id: title
            text: note.title
            anchors.right: parent.right
            anchors.left: image.right
            anchors.leftMargin: 5
            anchors.verticalCenter: image.verticalCenter
            elide: Text.ElideRight
        }
    }
}
