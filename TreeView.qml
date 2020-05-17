import QtQuick 2.14
import QtQuick.Layouts 1.14

Item {
    id: root

    property var parentIndex
    property var childCount
    property int itemLeftPadding: 30

    implicitWidth: parent.width
    implicitHeight: childrenRect.height

    ColumnLayout {
        width: parent.width
        spacing: 10

        Repeater {
            model: childCount

            delegate: Column {
                id: itemColumn

                Layout.fillWidth: true

                spacing: 10
                Layout.leftMargin: itemLeftPadding

                QtObject {
                    id: _d

                    property var currentIndex: _treemodel.index(index, 0, parentIndex)
                    property var currentData: _treemodel.data(currentIndex)
                    property var itemChildCount: _treemodel.rowCount(currentIndex)
                    property bool isOpen: false
                }

                Row {
                    spacing: 10
                    width: parent.width

                    MouseArea {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 15
                        height: 15
                        onClicked: _d.isOpen = !_d.isOpen

                        Rectangle {
                            anchors.verticalCenter: parent.verticalCenter
                            width: 15
                            height: 3
                            color: "#3c85b5"
                            opacity: _d.itemChildCount > 0 ? 1.0 : 0.0

                            Rectangle {
                                anchors.centerIn: parent
                                width: 3
                                height: 15
                                color: "#3c85b5"
                                visible: !_d.isOpen
                            }
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
                        font.pixelSize: 20
                    }

                }

                Rectangle {
                    anchors{
                        left: parent.left
                        leftMargin: -100
                        right: parent.right
                    }

                    height: 1
                    color: "gray"
                    opacity: 0.5
                }

                Loader {
                    width: parent.width

                    visible: _d.isOpen
                    source: "TreeView.qml"
                    onLoaded: {
                        item.parentIndex = _d.currentIndex
                        item.childCount = _d.itemChildCount
                    }
                }
            }
        }
    }
}
