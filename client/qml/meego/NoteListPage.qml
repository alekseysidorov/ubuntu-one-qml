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
			subtitle: truncate(note.content, 32)
			onClicked: {
				noteEditPage.note = note;
				pageStack.push(noteEditPage);
			}

			function truncate(str, n, suffix) {
				str = str.replace(/\r\n/g, "");
				if (suffix === undefined)
					suffix = "...";
				if (str.length > n)
					str = str.substring(0, n) + suffix;
				return str;
			}
		}
	}

	ScrollDecorator {
		flickableItem: listView
	}

}
