import QtQuick 1.0
import QtDesktop 0.1

Item {
    id: notesView
    property QtObject notes: null
    width: 800
    height: 600

    SplitterRow {
        anchors.fill: parent
        NotesListView {
            id: view

            width: 200
            notes: notesView.notes

            onCurrentNoteChanged: {
                console.log("Note" + view.currentNote);
            }
        }

        Item {
            id: noteProperties

            Column {
                id: notesRow
                anchors.fill: parent
                anchors.margins: 10

                spacing: 5

                Text {
                    id: title
                    text: view.currentNote.title
                    width: parent.width
                    font.bold: true
                }

                TextEdit {
                    id: area
                    text: view.currentNote.content
                    width: parent.width
                    wrapMode: Text.WordWrap

                    anchors.top: title.bottom
                    anchors.topMargin: 10
                    anchors.bottom: parent.bottom
                }
            }
        }
    }
}
