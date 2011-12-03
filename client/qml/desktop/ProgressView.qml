import QtQuick 1.0

Item {
	id: progress
	property bool running: false
	property string title: null
	visible: running
	width: 300
	height: 200

	Rectangle {
		id: background
		color: "#000"
		anchors.fill: parent
		opacity: 0
	}

	BusyIndicator {
		id: indicator
		anchors.centerIn: parent
		opacity: 0
	}
	Text {
		id: label
		text: title
		style: Text.Outline
		styleColor: "#d5d5d5"
		anchors.top: indicator.bottom
		anchors.topMargin: 5
		anchors.horizontalCenter: indicator.horizontalCenter
		opacity: 0.8
	}

	states: [
		State {
			name: "running"
			when: running
			PropertyChanges {
				target: background
				opacity: 0.2
			}
			PropertyChanges {
				target: indicator
				running: true
				opacity: 1
			}
		}
	]

	transitions: [
		Transition {
			PropertyAnimation {
				target: background
				properties: "opacity"
				duration: 200
			}
			PropertyAnimation {
				target: indicator
				properties: "opacity"
				duration: 300
			}
		}
	]

}
