import QtQuick 2.14

Item {
    id: root

    property var parentIndex
    property var childCount
    property int itemLeftPadding: 30

    width: childrenRect.width
    height: childrenRect.height

    Column {
        spacing: 10

        Repeater {
            model: childCount

            delegate: Column {
                id: itemColumn

                spacing: 10
                leftPadding: itemLeftPadding

                QtObject {
                    id: _d

                    property var currentIndex: _treemodel.index(index, 0, parentIndex)
                    property var currentData: _treemodel.data(currentIndex)
                    property var itemChildCount: _treemodel.rowCount(currentIndex)
                    property bool isOpen: false
                }

                Row {
                    spacing: 10

                    Rectangle {
                        width: 20
                        height: 20
                        color: _d.itemChildCount > 0 ? _d.isOpen ? "red" : "blue" : "transparent"

                        MouseArea {
                            anchors.fill: parent
                            onClicked: _d.isOpen = !_d.isOpen
                        }
                    }

                    Rectangle {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 20
                        height: 20
                        color: "#3c85b5"
                    }

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text:  _d.currentData
                        color: "#3c85b5"
                    }
                }

                Loader {
                    visible: _d.isOpen
                    source: "ItemView.qml"
                    onLoaded: {
                        item.parentIndex = _d.currentIndex
                        item.childCount = _d.itemChildCount
                    }
                }
            }
        }
    }
}
