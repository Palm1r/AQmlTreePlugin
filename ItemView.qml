import QtQuick 2.14

Item {
    id: root

    property var parentIndex
    property var childCount

    width: childrenRect.width
    height: childrenRect.height

    Column {
        spacing: 10

        Repeater {
            id: creator

            model: childCount

            delegate: Column {
                spacing: 5

                Rectangle {
                    QtObject {
                        id: _d

                        property var currentIndex: _treemodel.index(index, 0, parentIndex)
                        property var currentData: _treemodel.data(currentIndex)
                        property var itemChildCount: _treemodel.rowCount(currentIndex)
                    }

                    width: childrenRect.width
                    height: childrenRect.height

                    color: "green"

                    Row {
                        spacing: 10

                        Text {
                            text:  _d.currentData
                        }

                        Text {
                            text: _d.itemChildCount
                        }
                    }
                }

                Loader {
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
