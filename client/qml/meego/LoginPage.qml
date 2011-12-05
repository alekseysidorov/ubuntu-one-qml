import QtQuick 1.0
import com.nokia.meego 1.0
import "constants.js" as UI

Sheet {
	id: loginPage
	property alias email: loginInput.text
	property alias password: passwordInput.text

	content: Column {
		anchors.topMargin: UI.MARGIN_DEFAULT
		anchors.horizontalCenter: parent.horizontalCenter

		Image {
			id: logo
			source: "images/UbuntuOneLogo.svg"
		}

		Text {
			id: loginTitle

			width: parent.width
			text: qsTr("Email:")
			font.pixelSize: UI.FONT_DEFAULT_SIZE
			color: UI.LIST_TITLE_COLOR
		}

		TextField {
			id: loginInput
			width: parent.width
			KeyNavigation.tab: passwordInput
		}

		Text {
			id: passwordTitle

			width: parent.width
			text: qsTr("Password:")
			font.pixelSize: UI.FONT_DEFAULT_SIZE
			color: UI.LIST_TITLE_COLOR
		}

		TextField {
			id: passwordInput
			width: parent.width
			echoMode: TextInput.Password
			KeyNavigation.tab: loginButton
		}
	}
	acceptButtonText: qsTr("Login")
	rejectButtonText: qsTr("Cancel")
}
