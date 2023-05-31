import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Palm1r.treeviewProjects.RootController
import aqmltreeplugin
import "./"

Window {
    id: root

    visible: true
    width: 640
    height: 480
    title: qsTr("TreeView and ListView example")

    property var _treemodel: RootController.treeModel

    Row {
        id: buttonRow

        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: 60

        Button {
            width: parent.width / 2
            height: 40
            text: "Add item"
            font.pixelSize: 16

            onClicked: {
                var child = RootController.addItem("Child")
            }
        }

        Button {
            width: parent.width / 2
            height: 40
            text: "[WIP]//Remove item"
            font.pixelSize: 16
            opacity: 0.5
            enabled: false
        }
    }

    Row {
        id: views

        anchors {
            top: buttonRow.bottom
            bottom: parent.bottom
        }
        spacing: -1
        width: parent.width

        Rectangle {
            id: treePart

            width: parent.width / 2
            height: parent.height
            border {
                width: 1
                color: "gray"
            }
            clip: true

            Flickable {
                id: toolbarFlickable

                anchors.fill: parent
                contentHeight: tree.height
                contentWidth: parent.width
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar {}

                TreeItem {
                    id: tree

                    anchors {
                        top: parent.top
                        left: parent.left
                        leftMargin: 5
                        topMargin: 5
                    }

                    parentIndex: _treemodel.rootIndex()
                    childCount: _treemodel.rowCount(parentIndex)
                    itemLeftPadding: 0
                }
            }
        }

        Rectangle {
            id: listPart

            width: parent.width / 2
            height: parent.height
            border {
                width: 1
                color: "gray"
            }
            clip: true

            ListItem {
                anchors {
                    top: parent.top
                    left: parent.left
                    leftMargin: 5
                    topMargin: 5
                }

                itemLeftPadding: 0
            }
        }
    }
}
