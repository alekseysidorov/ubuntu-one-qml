import QtQuick 1.0
import QtDesktop 0.1

Item {
    id: noteEdit
    property QtObject note: null

    width: 600
    height: 400

    onNoteChanged: {
        titleEdit.text = note.title;
        contentEdit.text = note.content;
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

        onTextChanged: note.title = text;
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
           textFormat: TextEdit.RichText
           selectByMouse: true

           onTextChanged: note.content = text;
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
}
