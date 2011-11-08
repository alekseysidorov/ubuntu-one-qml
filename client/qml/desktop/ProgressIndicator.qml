import QtQuick 1.0
import UbuntuOne 0.1

ProgressIndicatorBase {
    id: indicator
    property bool playing : true
    width: 128
    height: 128

    RotationAnimation on angle {
        loops: Animation.Infinite
        from: 360
        to: 0
        running: playing
        duration: 1000
    }

}

//AnimatedImage
//{
//	id: image
//	source: "images/progressindicator.gif"
//	width: sourceSize.width
//	height: sourceSize.height

//}
