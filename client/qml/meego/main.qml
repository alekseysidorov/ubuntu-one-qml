import QtQuick 1.1
import com.nokia.meego 1.0
import com.ubuntu.one 1.0

PageStackWindow {
	id: appWindow
	initialPage: noteListPage
	showStatusBar: false

    Api {
        id: api

        Component.onCompleted: {
            if (!hasToken)
                loginDialog.open();
        }
    }

    LoginDialog {
        id: loginDialog
        onAccepted: {
            api.requestToken(email, password);
        }
    }

	NoteListPage {
		id: noteListPage
		notes: api.notes
		tools: commonTools
	}

	NoteEditPage {
		id: noteEditPage
	}

	AboutPage { id: aboutPage }

	ToolBarLayout {
		id: commonTools
		visible: true

		ToolIcon {
			iconId: "toolbar-add"
			onClicked: {
				noteEditPage.note = api.notes.create();
				pageStack.push(noteEditPage);
			}
		}
		ToolIcon {
			platformIconId: "toolbar-view-menu"
			anchors.right: (parent === undefined)? undefined: parent.right
			onClicked: (menu.status === DialogStatus.Closed)? menu.open(): menu.close()
		}
	}

	Menu {
		id: menu
		visualParent: pageStack
		MenuLayout {
			MenuItem {
				text: "About"
				onClicked: {menu.close(); pageStack.push(aboutPage)}
			}
			MenuItem {
				text: "Sync"
				onClicked: api.notes.sync();
			}
		}
	}
}
