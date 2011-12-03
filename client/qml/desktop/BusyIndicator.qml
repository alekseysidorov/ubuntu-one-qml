import QtQuick 1.0
import com.ubuntu.one 1.0

ProgressIndicatorBase {
    id: indicator
    property bool running : false
    width: 128
    height: 128
    leafCount: 18

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
