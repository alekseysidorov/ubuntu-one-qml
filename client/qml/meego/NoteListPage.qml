import QtQuick 1.1
import com.nokia.meego 1.0
import com.ubuntu.one 1.0

Page {
	id: noteListPage
	property QtObject notes: null
	tools: commonTools

	PageHeader {
		id: header
		text: qsTr("Notes:")
	}

	ListView {
		id: listView
		anchors.top: header.bottom
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.margins: 11
		clip: true
		focus: true
		model: notes.model
		delegate: ItemDelegate {			
			title: note.title
			subtitle: Qt.formatDateTime(note.createDate, "dd.MM.yyyy");
			onClicked: {
				noteEditPage.note = note;
				pageStack.push(noteEditPage);
			}
		}
	}

	ScrollDecorator {
		flickableItem: listView
	}

}
