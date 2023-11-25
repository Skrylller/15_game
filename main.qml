import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: _root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    GameBoard{
        anchors.fill: parent
    }
}
