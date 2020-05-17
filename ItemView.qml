import QtQuick 2.14

Item {
    id: root

    property var parentIndex
    property var childCount
    //    property var currentIndex:
    //    property var currentData: _treemodel.data(currentIndex)
    //    property var itemChildCount: _treemodel.rowCount(currentIndex)

    width: childrenRect.width
    height: childrenRect.height

    Column {
        spacing: 10

        Repeater {
            id: creator

            model: childCount

            delegate: Rectangle {
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
        }
    }

    //    property var currentIndex
    //    property var currentData
    //    property var itemChildCount

    //    Column {
    //        spacing: 10

    //        Repeater {
    //            model: _treemodel.rowCount(itemIndex)
    //            delegate: Rectangle {
    //                width: 50
    //                height: 30
    //                color: "green"

    ////                Text {
    ////                    text: _treemodel.data(itemIndex, 258)
    ////                }
    //            }
    //        }
    //    }
}
//Column{
//    id: root

//    height: childrenRect.height
//    width: childrenRect.width

//    Row{
//        id: itemView

//        spacing: 5
//        topPadding: 5
//        bottomPadding: 5

//        Text{
//            width: 10
//            height: 10
//            text: modelData.hasChild? modelData.isOpen ? "-" : "+" : ""

//            MouseArea{
//                anchors.fill: parent
//                onClicked: modelData.isOpen = !modelData.isOpen;
//            }
//        }

//        Rectangle {
//            height: content.height
//            width: height
//            color: "blue"
//        }

//        Text{
//            id: content

//            text: modelData.content
//        }
//    }

//    Loader{
//        source: modelData.isOpen ? "TreeItemsList.qml" : "Empty.qml"
//    }
//}
