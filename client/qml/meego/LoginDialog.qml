import QtQuick 1.0
import com.nokia.meego 1.0
import "constants.js" as UI

Dialog {
    id: loginDialog
    property alias email: loginInput.text
    property alias password: passwordInput.text

    title: Text {
        anchors.right: parent.right
        anchors.left: parent.left
        id: textheader
		font.pixelSize: UI.FONT_DEFAULT_SIZE
		color: UI.LIST_TITLE_COLOR_INVERTED
        text: qsTr("Welcome to Ubuntu One")
        wrapMode: Text.WordWrap
    }

    content: Column {
        anchors.centerIn: parent
        width: parent.width

        Text {
            id: loginTitle

            width: parent.width
            text: qsTr("Email:")
			font.pixelSize: UI.FONT_DEFAULT_SIZE
			color: UI.LIST_TITLE_COLOR_INVERTED
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
			color: UI.LIST_TITLE_COLOR_INVERTED
        }
        TextField {
            id: passwordInput
            width: parent.width
            echoMode: TextInput.Password
            KeyNavigation.tab: loginButton
        }
    }

    buttons: Button {
        id: loginButton
        width: parent.width
        text: "Login"
        KeyNavigation.tab: loginInput
        onClicked: {
            if (email.length > 0 && password.length > 0)
                loginDialog.accept();
        }
    }
}
