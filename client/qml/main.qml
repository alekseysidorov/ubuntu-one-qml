import QtQuick 1.0
import UbuntuOne 0.1
import QtDesktop 0.1
import QtWebKit 1.0

Rectangle {
	width: 300
	height: 400

	Frame {
		id: tokenRequestWindow

		anchors.fill: parent
		anchors.margins: 5
		visible: false

		Column {
			anchors.centerIn: parent

			spacing: 5

			Text {
				text: qsTr("Login:")

			}

			TextField {
				id: loginInput
				placeholderText: qsTr("Please input email")
			}

			Text {
				text: qsTr("Password:")
			}


			TextField {
				id: passwdInput
				passwordMode: true
			}

			Button {
				anchors.right: parent.right
				id: loginBtn
				text: qsTr("Login")
				defaultbutton: true
				onClicked: auth.requestToken(loginInput.text, passwdInput.text);
			}
		}
	}

	Frame {
		id: test

		anchors.fill: parent
		anchors.margins: 5
		visible: false

		Button {
			id: testButton
			text: qsTr("Test")
			onClicked: auth.notes.sync();
		}

		WebView {
			id: view
			anchors.top: testButton.bottom
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.bottom: parent.bottom
			anchors.margins: 10
		}
	}

	Auth {
		id: auth
		machine: "Robinhood"

		Component.onCompleted: {
			if (auth.hasToken)
				test.visible = true;
			else {
				tokenRequestWindow.visible = true;
			}
		}

		onTokenRequestFailed: {
			test.visible = false;
			tokenRequestWindow.visible = true;
		}
		onReceivedToken: {
			test.visible = true;
			tokenRequestWindow.visible = false;
		}
		onRedirect: {
			view.url = url;
		}
	}
}

