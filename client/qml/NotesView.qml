import QtQuick 1.0
import QtDesktop 0.1

Item {
    id: notesView
    property QtObject notes: null
    width: 800
    height: 600

    SplitterRow {
        anchors.fill: parent
        handleWidth: 1

        NotesListView {
            id: view

            width: 200
            notes: notesView.notes
        }

        NoteEdit {
            id: edit
            note: view.currentNote
        }
    }
}
