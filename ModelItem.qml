import QtQuick 2.14

Row {
    id: root

    property alias content: contentData.text

    spacing: 10

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        width: 20
        height: 20
        color: "#3c85b5"
    }

    Text {
        id: contentData

        anchors.verticalCenter: parent.verticalCenter
        color: "#3c85b5"
        font.pixelSize: 20
    }
}
