import QtQuick 2.14
import "./"

Column{
    id: root

    property var parentIndex
    property var childCount

    leftPadding: 10

    Repeater{
        model: childCount
        delegate: ItemView{
            id: delegateItem

            parentIndex: root.parentIndex
            childCount: root.childCount
        }
    }
}
