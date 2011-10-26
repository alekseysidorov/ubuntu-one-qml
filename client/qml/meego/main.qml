import QtQuick 1.0
import com.nokia.meego 1.0
import UbuntuOne 0.1

PageStackWindow {
    id: rootWindow
    initialPage: Page {
        tools: ToolBarLayout {
            ButtonRow {
                style: TabButtonStyle { }
                TabIcon {
                    platformIconId: "toolbar-settings"
                }
            }
        }
    }

    Api {
        id: api

        Component.onCompleted: {
            if (!hasToken)
                loginDialog.open();
        }
    }

    LoginDialog {
        id: loginDialog
        onAccepted: {
            api.requestToken(email, password);
        }
    }
}
