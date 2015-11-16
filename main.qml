import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import CharacterLib 1.0

Window {
    id: window1
    visible: true
    minimumWidth: 480
    minimumHeight: 640
    width: 480
    height: 640

    Rectangle {
        id: rectangle2
        color: "#4d4d4d"
        anchors.fill : parent

        Rectangle {
            id: logoBorder
            height: 114
            color: "#aaaaaa"
            anchors.rightMargin: 8
            anchors.leftMargin: 8
            anchors.topMargin: 8
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top

            Image {
                id: logo
                x: 0
                width: 480
                height: 122
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
                source: "images/logo.png"
            }
        }

        CharacterManager
        {
            id: characterManager

        }

        Rectangle {
            id: listBorder
            color: "#aaaaaa"
            anchors.bottomMargin: 86
            anchors.leftMargin: 8
            anchors.rightMargin: 8
            anchors.topMargin: 128
            anchors.fill: parent
            clip: true

            ScrollView {
                anchors.fill: parent

                ListView {
                    id: characterList
                    width: parent.width
                    height: 426
                    model: characterManager
                    highlight: Rectangle {
                        color:"white"
                        radius: 5
                        opacity: 0.7
                        focus: true
                    }
                    delegate: Rectangle {
                        id: characterListItem
                        width: parent.width
                        height: 40
                        color: "transparent"
                        border.width: 3
                        border.color: "black"
                        Row {
                            x: 5
                            id: row1
                            height: parent.height
                            Text {
                                text: display
                                anchors.verticalCenter: parent.verticalCenter
                                font.bold: true
                                color: "black"
                            }
                            spacing: 10
                        }

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: false
                            onClicked: characterList.currentIndex = index
                        }
                    }
                }
            }
        }

        Rectangle {
            id: playBtn
            y: 560
            height: 70
            color: "#aaaaaa"
            anchors.right: parent.right
            anchors.rightMargin: 178
            anchors.left: parent.left
            anchors.leftMargin: 178
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8

            Image {
                id: image1
                width: 108
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectFit
                source: "images/play.png"
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked: characterManager.playAsCharacter(characterList.currentIndex)
            }
        }

        Rectangle {
            id: deleteBtn
            x: 311
            y: 560
            width: 160
            height: 70
            color: "#aaaaaa"
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8

            Image {
                id: image2
                width: 144
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectFit
                source: "images/delete.png"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: characterManager.deleteCharacter(characterList.currentIndex)
            }
        }

        Rectangle {
            id: newBtn
            x: 8
            y: 560
            width: 160
            height: 70
            color: "#aaaaaa"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8

            Image {
                id: image3
                width: 144
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectFit
                source: "images/new.png"
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked: characterManager.newCharacter()
            }
        }
    }
}

