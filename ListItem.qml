import QtQuick 2.14

Item {
    id: root

    property var parentIndex
    property var childCount
    property int itemLeftPadding: 30

    anchors.fill: parent

    onParentIndexChanged: {
        fillData()
    }

    ListModel {
        id: listItemModel
    }

    ListView {
        id: listArea

        anchors.fill: parent
        spacing: 10
        boundsBehavior: Flickable.StopAtBounds

        model: listItemModel
        delegate: Column {
            width: parent.width
            spacing: 10

            ModelItem {
                content: name
            }

            Rectangle {
                anchors {
                    left: parent.left
                    leftMargin: -100
                    right: parent.right
                }

                width: parent.width
                height: 1
                color: "gray"
                opacity: 0.5
            }
        }
    }

    function fillData() {
        let rootIndex = _treemodel.rootIndex()

        for(var i = 0; i < _treemodel.rowCount(rootIndex); i++) {
            let index =_treemodel.index(i, 0, rootIndex)
            listItemModel.append({"name":  _treemodel.data(index)})
            fillFromBranch(index)
        }
    }

    function fillFromBranch(modelIndex) {
        let childCount = _treemodel.rowCount(modelIndex)

        if (childCount > 0) {
            for (var i = 0; i < childCount; i++) {
                let index =_treemodel.index(i, 0, modelIndex)
                listItemModel.append({"name":  _treemodel.data(index)})
                fillFromBranch(index)
            }
        }
    }
}
