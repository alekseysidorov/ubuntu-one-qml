import QtQuick 1.0
import QtDesktop 0.1

Item {
    id: listView
    property QtObject notes: null

    StyleItem {
        id: header

        elementType: "header"
        text: qsTr("Notes")
        info: "only"
        raised: true
        width: parent.width
        height: 25

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
    }

    ListView {
        id: view
        clip: true
        model: notes.model

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header.bottom
        anchors.bottom: footer.top

        delegate: Text {
            id: delegate
            width: parent.width
            text: note.title
            elide: Text.ElideRight

            Rectangle {
                anchors.fill: parent
                color: "black"
                opacity: index % 2 ? 0.05 : 0
            }
        }
    }

    StyleItem {
        id: footer

        elementType: "header"
        info: "only"
        raised: true
        height: childrenRect.height
        rotation: 180

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Row {
            rotation: -180

            ToolButton {
                id: syncBtn
                iconName: "folder-sync"

                onClicked: notes.sync()
            }
        }
    }

}
