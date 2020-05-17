import QtQuick 2.14
import QtQuick.Window 2.14
import "./"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("TreeView example")

    ItemView {
        anchors.fill: parent
        parentIndex: _treemodel.rootIndex()
        childCount: _treemodel.rowCount(parentIndex)
    }
}
