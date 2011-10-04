import QtQuick 1.0
import QtDesktop 0.1

Item {
    id: noteEdit
    property QtObject note: null

    width: 600
    height: 400

    TextInput {
        id: titleEdit
        font.bold: true
        text: note.title
        selectByMouse: true

        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
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
           text: note.content
           wrapMode: TextEdit.WordWrap
           textFormat: TextEdit.RichText
           selectByMouse: true
       }
    }
}
