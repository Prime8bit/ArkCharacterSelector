import QtQuick 2.3
import QtQuick.Window 2.2
import CharacterLib 1.0

Window {
    visible: true
    width: 480
    height: 640

    Rectangle {
        color: "#4d4d4d"
        anchors.fill : parent

        Image {
            id: logo
            x: 0
            y: 0
            width: 480
            height: 122
            fillMode: Image.PreserveAspectFit
            source: "qrc:/assets/images/logo.png"
        }

        CharacterManager
        {
            id: characterListModel

        }

        ListView {
            id: characterList
            x: 0
            y: 128
            width: 472
            height: 504
            model: characterListModel
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    Rectangle {
                        width: 40
                        height: 40
                        color: "red"
                    }

                    Text {
                        text: display
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }
                    spacing: 10
                }
            }
        }

    }
}

