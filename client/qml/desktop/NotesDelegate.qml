import QtQuick 1.0
import com.ubuntu.one 1.0

Component {
    Item {
        id: root
        width: parent.width
        height: 30

        SystemPalette {
            id: pal
        }

        Rectangle {
            id: background
            anchors.fill: parent
            color: pal.alternateBase
            opacity: index % 2 ? 1 : 0
        }

        Image {
            id: image

            anchors.verticalCenterOffset: 0
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter

            sourceSize.height: 22
            sourceSize.width: 22
            source: "images/note.svgz"
            rotation: 0

            RotationAnimation on rotation {
                id: rotation
                loops: Animation.Infinite
                from: 0
                to: 360
                duration: 2000
                running: false
            }
        }

        Text {
            id: title
            text: note.title
            anchors.right: parent.right
            anchors.left: image.right
            anchors.leftMargin: 5
            anchors.verticalCenter: image.verticalCenter
            elide: Text.ElideRight
        }

        states: [
            State {
                name: "syncing"
                when: note.status === Note.StatusSyncing

                PropertyChanges {
                    target: image
                    source: "images/busy.png"
                }
                PropertyChanges {
                    target: rotation
                    running: true
                }
            },
            State {
                name: "remoral"
                when: note.status === Note.StatusRemoral

                PropertyChanges {
                    target: image
                    source: "images/busy.png"
                }

                PropertyChanges {
                    target: rotation
                    running: true
                }
            },
            State {
                name: "actual"
                when: note.status === Note.StatusActual
                PropertyChanges {
                    target: image
                    rotation: 0
                }
            }

        ]
    }
}
