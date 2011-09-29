import QtQuick 1.1
import QtDesktop 0.1

Column {
	id: loginDialog

	property QtObject api
	property string email : loginField.text
	property string password
	property bool running: false

	signal started
	signal finished (bool success)

	spacing: 5

	add: Transition {
		NumberAnimation { properties: "y"; easing.type: Easing.OutQuad; duration: 300 }
	}

	onFinished: {
		running = false;
	}

	Image {
		id: logo
		source: "images/UbuntuOneLogo.svg"
		anchors.horizontalCenter: parent.horizontalCenter
	}

	Text {
		id: loginTitle
		text: qsTr("Login")
	}

	TextField {
		id: loginField
		placeholderText: qsTr("Please input email")

		KeyNavigation.tab: passwordField
	}

	Text {
		id: passwordTitle
		text: qsTr("Password")
	}

	TextField {
		id: passwordField
		placeholderText: qsTr("...")
		passwordMode: true

		KeyNavigation.tab: loginButton
	}

	Item {
		id: spacer
		height: 10
		width: parent.width
	}

	Button {
		id: loginButton
		text: qsTr("Login")

		KeyNavigation.tab: loginField

		onClicked: {
			running = true;
			loginDialog.started();
			api.requestToken(loginField.text, passwordField.text);
		}
	}

	Connections {
		target: api

		onAuthorizationFailed: {
			loginDialog.finished(false);
		}

		onAuthorized: {
			loginDialog.finished(true);
		}
	}

	states: [
		State {
			name: "running"
			PropertyChanges {
				target: passwordField
				readOnly: true
			}
			PropertyChanges {
				target: loginField
				readOnly: true
			}
		}
	]
}
