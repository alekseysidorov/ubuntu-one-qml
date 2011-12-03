// Emulates the page header of some N9 apps

import QtQuick 1.0
import com.nokia.meego 1.0

Rectangle {
	id: pageHeader

	property string text: "Page Title"
	property bool clickable: false   // Set to true to show a combobox indicator
	signal clicked

	height: 65
	color: "orange"
	anchors.top: parent.top
	anchors.left: parent.left
	anchors.right: parent.right

	Label {
		anchors.fill: parent
		anchors.leftMargin: 19
		anchors.topMargin: 17
		text: pageHeader.text
		font.pixelSize: 32
		color: "white"
		elide: Text.ElideRight
	}

	Image {
		anchors.top: parent.top
		anchors.right: parent.right
		anchors.rightMargin: 19
		anchors.topMargin: 19
		source: "image://theme/meegotouch-combobox-indicator-inverted"
		visible: pageHeader.clickable
	}

	MouseArea {
		anchors.fill: parent
		onClicked: {
			console.log("* PageHeader clicked")
		}

		// Forward "clicked" signal on completion
		Component.onCompleted: {
			clicked.connect(pageHeader.clicked)
		}
	}
}
