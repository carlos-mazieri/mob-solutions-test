import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4

TableView {
    id: root
    anchors.fill: parent
    clip: true

    Component {
        id: columnComponent
        TableViewColumn { width: 150 }
    }
    Component.onCompleted:
    {
        var roleList = gadgetHelper.columnList();
        for(var i=0; i<roleList.length; i++)
        {
            var role  = roleList[i]         
            var column = columnComponent.createObject(root, { "role": role, "title": role})
            root.addColumn(column);
        }
    }

    model: CustomModel {
      id: fuzzyModel
      numberOfRows: 15
    }
}
