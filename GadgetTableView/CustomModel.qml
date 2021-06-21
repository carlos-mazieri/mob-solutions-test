import QtQuick 2.0
import QtQml.Models 2.15


ListModel
{
    id: root
    property int numberOfRows: 1
    Component.onCompleted:
    {
        for(var i=0; i< root.numberOfRows; ++i)
        {
            root.append(gadgetHelper.generateModelRow());
        }
    }
}
