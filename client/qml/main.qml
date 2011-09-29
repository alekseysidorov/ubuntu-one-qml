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
			api: api
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

			Row {
				id: row

				Button {
					id: testButton
					text: qsTr("Test account")
					onClicked: {
						progressView.running = true;
						progressView.title = qsTr("Loading account info...")
						api.account.updateInfo();
					}
				}

				Button {
					id: testButton2
					text: qsTr("Test notes")
					onClicked: {
						progressView.running = true;
						progressView.title = qsTr("Loading notes...")
						api.notes.sync();
					}
				}

			}

			AccountView {
				id: view
				account: api.account
				anchors.bottom: parent.bottom
				anchors.top: row.bottom
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.topMargin: 10
			}

		}
	}

	ProgressView {
		id: progressView
		anchors.fill: parent

		Connections {
			target: api.account
			onInfoUpdated: {
				progressView.running = false;
				progressView.title = "";
			}
		}
	}

	Api {
		id: api
		machine: "Robinhood"

		Component.onCompleted: {
			if (api.hasToken)
				test.visible = true;
			else {
				tokenRequestWindow.visible = true;
			}
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

