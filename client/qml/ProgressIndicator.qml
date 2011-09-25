import QtQuick 1.0

Image {
	id: image
	property bool playing : true

	source: "images/progressindicator.gif"
	width: sourceSize.width
	height: sourceSize.height


	RotationAnimation on rotation {
		loops: Animation.Infinite
		from: 0
		to: 360
		running: playing
		duration: 5000
	}

}

//AnimatedImage
//{
//	id: image
//	source: "images/progressindicator.gif"
//	width: sourceSize.width
//	height: sourceSize.height

//}
