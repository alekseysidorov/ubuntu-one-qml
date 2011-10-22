import QtQuick 1.0
import QtDesktop 0.1

Item {
    id: listView
    property QtObject notes: null
    property QtObject currentNote: null

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

    NotesDelegate {
        id: notesDelegate
    }

    ListView {
        id: view
        clip: true
        model: notes.model
        highlightFollowsCurrentItem: true
        keyNavigationWraps: true

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header.bottom
        anchors.bottom: footer.top

        delegate: notesDelegate

        //highlight: Rectangle {
        //    color: "blue"
        //}

        MouseArea {
            anchors.fill: parent
            onClicked: {
                var index = view.indexAt(mouse.x, mouse.y);
                if (index !== -1 && index < notes.model.count)
                    currentNote = notes.model.get(index);
                else
                    currentNote = null;
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
                iconName: "list-add"
                tooltip: qsTr("Add a new note")

                onClicked: {
                    currentNote = notes.create();
                }
            }
        }
    }

}
