import QtQuick 2.12
import QtQuick.Window 2.0
import com.test.models 1.0


TableView {
    id: root
    anchors.fill: parent
    anchors.margins: 20
    rowSpacing: 5
    columnSpacing: 5

    clip: true
    visible: true

    delegate: cellDelegate

    model: CustomModel {
        id: fuzzyModel
        numberOfRows: 15
    }

    // a delegate is mandaory to have a call to QAbstractTableModel::data()
    Component {
        id: cellDelegate

        Rectangle {
            border.color: "black"
      //      color: row === 0 ? "lightgreen" : "transparent"
            implicitHeight: 40
            implicitWidth: 80

            Text {
                anchors.centerIn: parent
                text: display
            }
        }
    }
}
