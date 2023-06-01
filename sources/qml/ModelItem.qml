import QtQuick

Row {
    id: root

    property alias content: contentData.text

    signal selected

    spacing: 10

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        width: 20
        height: 20
        color: "#3c85b5"

        MouseArea {
            anchors.fill: parent
            onClicked: root.selected()
        }
    }

    Text {
        id: contentData

        anchors.verticalCenter: parent.verticalCenter
        color: "#3c85b5"
        font.pixelSize: 20
    }
}
