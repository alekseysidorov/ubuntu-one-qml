import QtQuick 1.1
import com.nokia.meego 1.0
import com.ubuntu.one 1.0
import "constants.js" as UI

Page {
	id: noteEditPage
	property QtObject note: undefined

	tools: 	ToolBarLayout {
		visible: true
		ToolIcon {
			iconId: "toolbar-back"
			onClicked: {
				note.content = textField.text;
				note.title = header.title;
				note.save();
				pageStack.pop()
			}
		}
		ToolIcon {
			platformIconId: "toolbar-delete"
			anchors.right: (parent === undefined) ? undefined: parent.right
			onClicked: {
				note.remove();
				pageStack.pop();
			}
		}
	}

	PageHeader {
		id: header
		property string title: note.title
		text: qsTr("Edit:") + title
		clickable: true
		onClicked: {
			noteTitleChange.text = title;
			noteTitleChange.open();
		}
	}

	Dialog {
		id: noteTitleChange
		property alias text: noteTitleField.text

		buttons: Button {
			text: qsTr("Update")
			onClicked: noteTitleChange.accept();
			width: parent.width
		}
		title: Text {
			text: qsTr("Update note title: ")
			font.pixelSize: UI.FONT_DEFAULT_SIZE
			color: UI.LIST_TITLE_COLOR_INVERTED
			width: parent.width
		}
		content: TextField {
			id: noteTitleField
			width: parent.width
		}
		onAccepted: {
			noteEditPage.note.title = noteTitleField.text;
		}
	}

	TextFieldStyle {
		id: textFieldStyle
		background: "transparent"
		backgroundSelected: "transparent"
		backgroundError: "transparent"
	}

	TextArea {
		id: textField
		anchors {
			left: parent.left;
			right: parent.right;
			bottom: parent.bottom;
			top: header.bottom
		}
		text: note.content
		style: textFieldStyle
	}
}
