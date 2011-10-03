import QtQuick 1.0
import UbuntuOne 0.1
import QtDesktop 0.1
import QtWebKit 1.0

Rectangle {
    width: 800
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

    Item {
        id: test

        anchors.fill: parent
        visible: false

        Item {
            anchors.fill: parent

            ToolBar {
                id: toolBar

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right

                Row {

                    ToolButton {
                        id: sync
                        tooltip: qsTr("Sync")
                        iconName: "folder-sync"

                        onClicked: api.notes.sync();
                    }

                    ToolButton {
                        id: purgeBtn
                        tooltip: qsTr("Purge")
                        iconName: "edit-clear"

                        onClicked: api.purge();
                    }

                }
            }

            NotesView {
                id: notesView
                notes: api.notes

                anchors.top: toolBar.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }

            //			Row {
            //				id: row

            //				Button {
            //					id: testButton
            //					text: qsTr("Test account")
            //					onClicked: {
            //						progressView.running = true;
            //						progressView.title = qsTr("Loading account info...")
            //						api.account.updateInfo();
            //					}
            //				}

            //				Button {
            //					id: testButton2
            //					text: qsTr("Test notes")
            //					onClicked: {
            //						progressView.running = true;
            //						progressView.title = qsTr("Loading notes...")
            //						api.notes.sync();
            //					}
            //				}

            //			}

            //			AccountView {
            //				id: view
            //				account: api.account
            //				anchors.bottom: parent.bottom
            //				anchors.top: row.bottom
            //				anchors.left: parent.left
            //				anchors.right: parent.right
            //				anchors.topMargin: 10
            //			}

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

        function checkToken()
        {
            if (api.hasToken)
                test.visible = true;
            else {
                tokenRequestWindow.visible = true;
            }
        }

        Component.onCompleted: checkToken()
        onHasTokenChanged: checkToken()
    }

    Connections {
        target: loginDialog

        onStarted: {
            progressView.title = qsTr("Authorization...")
            progressView.running = true;
        }

        onFinished: {
            progressView.running = false;
            tokenRequestWindow.visible = !success
            test.visible = success;
        }
    }

}

