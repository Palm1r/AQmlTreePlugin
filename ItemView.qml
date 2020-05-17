import QtQuick 2.14

Column{
    id: root

    height: childrenRect.height
    width: childrenRect.width

    Row{
        id: itemView

        spacing: 5
        topPadding: 5
        bottomPadding: 5

        Text{
            width: 10
            height: 10
            text: modelData.hasChild? modelData.isOpen ? "-" : "+" : ""

            MouseArea{
                anchors.fill: parent
                onClicked: modelData.isOpen = !modelData.isOpen;
            }
        }

        Rectangle {
            height: content.height
            width: height
            color: "blue"
        }

        Text{
            id: content

            text: modelData.content
        }
    }

    Loader{
        source: modelData.isOpen ? "TreeItemsList.qml" : "Empty.qml"
    }
}
