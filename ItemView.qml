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
                    id: item2

                    property var currentIndex2: _treemodel.index(index, 0, parentIndex)
                    property var currentData2: _treemodel.data(currentIndex2)
                    property var itemChildCount2: _treemodel.rowCount(currentIndex2)

                    width: childrenRect.width
                    height: childrenRect.height

                    color: "green"

                    Row {
                        spacing: 10

                        Text {
                            text: item2.currentData2
                        }

                        Text {
                            text: item2.itemChildCount2
                        }
                    }
                }

                Loader {
                    source: "ItemView.qml"
                    onLoaded: {
                        item.parentIndex = item2.currentIndex2
                        item.childCount = item2.itemChildCount2
                    }
                }
            }
        }
    }
}
