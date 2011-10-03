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
        }

        Item {
            id: noteProperties

            Row {
                id: notesRow
                anchors.fill: parent
            }
        }
    }
}
