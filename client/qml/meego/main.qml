import QtQuick 1.1
import com.nokia.meego 1.0
import com.ubuntu.one 1.0

PageStackWindow {
	id: appWindow
	initialPage: noteListPage

	Api {
		id: api
		Component.onCompleted: checkToken()
		onHasTokenChanged: checkToken()

		function checkToken() {
			if (!hasToken)
				loginPage.open();
			else
				api.notes.sync();
		}
	}

	BusyIndicator {
		id: spinner
		platformStyle: BusyIndicatorStyle {size: "large"}
		anchors.centerIn: parent
		focus: false
		visible: api.notes.busy
	}


	LoginPage {
		id: loginPage
		onAccepted: api.requestToken(email, password);
	}

	NoteListPage {
		id: noteListPage
		notes: api.notes
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
				text: qsTr("About")
				onClicked: {menu.close(); pageStack.push(aboutPage)}
			}
			MenuItem {
				text: qsTr("Sync")
				onClicked: api.notes.sync();
			}
			MenuItem {
				text: api.hasToken ? qsTr("Logout") : qsTr("Login")
				onClicked: {
					if (api.hasToken)
						api.purge();
					else
						loginPage.open();
				}
			}
		}
	}
}
