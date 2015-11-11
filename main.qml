import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true
    width: 480
    height: 640

    Rectangle {
        anchors.fill : parent

        Image {
            id: image1
            x: 0
            y: 0
            width: 480
            height: 122
            fillMode: Image.PreserveAspectFit
            source: "qrc:/qtquickplugin/images/template_image.png"
        }

        Rectangle {
            id: rectangle1
            x: 8
            y: 128
            width: 464
            height: 369
            color: "#ffffff"
        }

    }
}

