import QtQuick 1.0
import UbuntuOne 0.1

Rectangle {
    width: 360
    height: 360
    Text {
        anchors.centerIn: parent
        text: "Hello World"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
			auth.login();
        }
    }

	Auth {
		id: auth
	}
}
