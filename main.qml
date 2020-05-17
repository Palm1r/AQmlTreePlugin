import QtQuick 2.14
import QtQuick.Window 2.14
import "./"

Window {
    id: root

    visible: true
    width: 640
    height: 480
    title: qsTr("TreeView example")

    Rectangle {
        width: parent.width / 2
        height: parent.height
        border {
            width: 1
            color: "gray"
        }

        TreeView {
            parentIndex: _treemodel.rootIndex()
            childCount: _treemodel.rowCount(parentIndex)
            itemLeftPadding: 0
        }
    }
}
