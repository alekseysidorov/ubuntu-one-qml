import QtQuick 1.0
import UbuntuOne 0.1
import QtDesktop 0.1

Rectangle {
	width: 300
	height: 400

	Frame {
		anchors.fill: parent
		anchors.margins: 5

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
				onClicked: auth.login();
			}
		}
	}

	Auth {
		id: auth
		userName: loginInput.text
		password: passwdInput.text
		machine: "Robinhood"
	}
}

