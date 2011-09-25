import QtQuick 1.0
import QtDesktop 0.1

Item {
	id: accountView
	property QtObject account: null
	width: 400
	height: 600

	Item {
		id: progress
		z: 1
		anchors.fill: parent

		Rectangle {
			id: background
			color: "#000"
			anchors.fill: parent
			opacity: 0
		}

		ProgressIndicator {
			id: indicator
			anchors.centerIn: parent
			opacity: 0
		}

	}

	Flickable {
		id: flickable
		anchors.fill: parent
		clip: true
		contentWidth: accountForm.width
		contentHeight: accountForm.height

		Column {
			id: accountForm
			spacing: 5

			AccountItem {
				id: firstName
				label: qsTr("First Name");
			}

			AccountItem {
				id: lastName
				label: qsTr("Last Name");
			}

			AccountItem {
				id: nickname
				label: qsTr("Nick");
			}

			AccountItem {
				id: email
				label: qsTr("Email");
			}

			Text {
				text: qsTr("Current Plan:")
			}

			Text {
				id: currentPlan
				width: parent.width
				wrapMode: Text.Wrap
			}
		}

	}

	Connections {
		target: account
		onInfoUpdated: {
			firstName.value = info.first_name;
			lastName.value = info.last_name;
			email.value = info.email;
			nickname.value = info.nickname;
			currentPlan.text = info.current_plan;

			var text = "";
			for (var p in info) {
				text = text + p + " : " + info[p] + "\n ";
				console.log(p);
			}
			//accountInfo.text = text;
		}
	}
}
