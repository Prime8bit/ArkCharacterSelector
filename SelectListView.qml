import QtQuick 2.0

ListView {
    id: selectList

    property color darkColor : "#111"
    property color lightColor : "#222"
    property color textColor : "white"

    width: 400
    height: 200

    model: pythonListModel

    delegate: Component {
        Rectangle {
            width: selectList.width
            height: 40
            color: ((index % 2 == 0)? selectList.lightColor : selectList.darkColor)
            Text {
                id: title
                elide: Text.ElideRight
                text: model.thing.name
                color: selectList.textColor
                font.bold: true
                anchors.leftMargin: 10
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: { controller.thingSelected(model.thing) }
            }
        }
    }
}

