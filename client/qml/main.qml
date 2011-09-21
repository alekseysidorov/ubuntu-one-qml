import QtQuick 1.0
import UbuntuOne 0.1
import QtDesktop 0.1

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

	Button {
		id: testButton
		text: qsTr("Test")
		visible: false
		onClicked: auth.test();
	}

	Auth {
		id: auth
		machine: "Robinhood"

		Component.onCompleted: {
			if (auth.hasToken)
				testButton.visible = true;
			else {
				tokenRequestWindow.visible = true;
			}
		}

		onTokenRequestFailed: {
			testButton.visible = false;
			tokenRequestWindow.visible = true;
		}
		onReceivedToken: {
			testButton.visible = true;
			tokenRequestWindow.visible = false;
		}
	}
}

