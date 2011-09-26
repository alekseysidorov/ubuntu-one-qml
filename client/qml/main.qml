import QtQuick 1.0
import UbuntuOne 0.1
import QtDesktop 0.1
import QtWebKit 1.0

Rectangle {
	width: 400
	height: 600

	Frame {
		id: tokenRequestWindow

		anchors.fill: parent
		anchors.margins: 5
		visible: false

		LoginDialog {
			id: loginDialog
			anchors.centerIn: parent
			api: auth
		}
	}

	Frame {
		id: test

		anchors.fill: parent
		anchors.margins: 5
		visible: false

		Item {
			anchors.fill: parent
			anchors.margins: 5

			Button {
				id: testButton
				text: qsTr("Test")
				onClicked: {
					progressView.running = true;
					progressView.title = qsTr("Loading account info...")
					auth.account.updateInfo();
				}
			}

			AccountView {
				id: view
				account: auth.account
				anchors.bottom: parent.bottom
				anchors.top: testButton.bottom
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.topMargin: 10
			}

		}

		//WebView {
		//	id: view
		//	anchors.top: testButton.bottom
		//	anchors.left: parent.left
		//	anchors.right: parent.right
		//	anchors.bottom: parent.bottom
		//	anchors.margins: 10
		//}
	}

	ProgressView {
		id: progressView
		anchors.fill: parent

		Connections {
			target: auth.account
			onInfoUpdated: {
				progressView.running = false;
				progressView.title = "";
			}
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

		onRedirect: {
			view.url = url;
		}
	}

	Connections {
		target: loginDialog

		onStarted: {
			progressView.title = qsTr("Authorization...")
			progressView.running = true;
		}

		onFinished: {
			progressView.running = false;
			loginDialog.visible = !success
			test.visible = success;
		}
	}

}

