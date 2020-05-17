import QtQuick 2.14
import QtQuick.Window 2.14
import "./"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("TreeView example")

    TreeView {
        anchors.fill: parent
        anchors.leftMargin: 5
        parentIndex: _treemodel.rootIndex()
        childCount: _treemodel.rowCount(parentIndex)
        itemLeftPadding: 0
    }
}
