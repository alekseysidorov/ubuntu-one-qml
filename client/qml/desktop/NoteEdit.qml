import QtQuick 1.0
import QtDesktop 0.1

Item {
    id: noteEdit
    property QtObject note: null

    width: 600
    height: 400
    state: "welcome"

    onNoteChanged: {

        onNoteChanged: {
            console.log(note);
            if (note) {
                titleEdit.text = note.title;
                contentEdit.text = note.content;
            } else {
                titleEdit.text = qsTr("Welcome to notes client");
                contentEdit.text = qsTr("Click to add note");
            }
        }

        //state = note ? "edit" : "welcome";
    }

    TextInput {
        id: titleEdit
        font.bold: true
        selectByMouse: true

        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5

        onTextChanged: {
            if (note)
                note.title = text;
        }
    }

    Flickable {
        id: flickable
        contentHeight: contentEdit.height
        clip: true

        anchors.bottom: parent.bottom
        anchors.right: titleEdit.right
        anchors.left: titleEdit.left
        anchors.top: titleEdit.bottom
        anchors.topMargin: 10

        TextEdit {
            id: contentEdit

            width: flickable.width
            wrapMode: TextEdit.WordWrap
            textFormat: TextEdit.PlainText
            selectByMouse: true

            onTextChanged: {
                if (note)
                    note.content = text;
            }
        }
    }

    Row {
        anchors.bottom: parent.bottom

        Button {
            id: syncBtn
            text: qsTr("save")
            onClicked: note.sync()
        }

        Button {
            id: removeBtn
            text: qsTr("remove")
            onClicked: note.remove()
        }
    }

    //states: [
    //    State {
    //        name: "welcome"
    //        PropertyChanges {
    //            target: titleEdit
    //            readOnly: true
    //            text: qsTr("Welcome to notes client")
    //        }
    //        PropertyChanges {
    //            target: contentEdit
    //            readOnly: true
    //            text: qsTr("Click to add note")
    //        }
    //    },
    //    State {
    //        name: "edit"
    //        StateChangeScript {
    //            name: "editScript"
    //            script: {
    //                console.log("Script + " + note.title);
    //                titleEdit.text = note.title;
    //                contentEdit.text = note.content;
    //            }
    //        }

    //    }
    //]
}
