import QtQuick 2.14
import "./"

Column{
    leftPadding: 10

    Repeater{
        model: modelData.childItems
        delegate: ItemView{}
    }
}
