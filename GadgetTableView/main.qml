import QtQuick 2.12
import QtQuick.Window 2.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Gadgate TableView")

    CustomTableView {
        id: tableView    
    }
}
