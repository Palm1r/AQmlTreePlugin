import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 1.4
import "./"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("TreeView example")

    ListView {
        anchors.fill: parent
        spacing: 10
        model: _treemodel

        delegate: Rectangle {
            width: childrenRect.width
            height: 40
            color: "red"

            Row {
                spacing: 10

                Text {
                    text: _treemodel.data(_treemodel.index(index, 0))
                }

                Text {
                    text: _treemodel.rowCount(_treemodel.index(index, 0))
                }
            }
        }
    }
    //    ListView{
    //        anchors.fill: parent
    //        anchors.margins: 10
    //        model: _treemodel
    //        delegate: ItemView{}
    //    }
}
