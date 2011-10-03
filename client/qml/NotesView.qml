import QtQuick 1.0
import QtDesktop 0.1

Item {
    id: notesView
    property QtObject notes: null

    width: 600
    height: 400

    Frame {
        id: notesList
        width: 250

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5

        ListView {
            id: view
            anchors.fill: parent

            clip: true
            model: notes.model
            delegate: ToolButton {
                id: text
                width: view.width
                text: note.title
                tooltip: note.content
            }
        }
    }

    Item {
        id: noteProperties

        anchors.left: notesList.right
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 0

        Row {
            id: notesRow
            anchors.fill: parent

            Button {
                id: sync
                text: qsTr("Sync")
                onClicked: {
                    notes.sync();
                }
            }
        }
    }
}
