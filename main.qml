import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: _root

    readonly property int infoPanelSize: 200;

    visible: true;
    width: 640;
    height: 480;
    title: qsTr("15 to match");

    Rectangle{
        id: _mainRect;
        width: _root.width;
        height: _root.height;
        color: "lightblue";

        Rectangle{
            id: _infoRect;
            color: "steelblue";
            anchors.fill: parent;
            anchors.leftMargin: _root.width - infoPanelSize;

            border.color: "black";
            border.width: 1;

            Column {
                id: _infoColumn;

                property int paddings: 20

                anchors.fill: parent;
                anchors.margins: paddings;

                spacing: paddings

                TimePanel{

                }
            }
        }

        GameBoard{
            anchors.fill: parent;
            anchors.rightMargin: infoPanelSize;
        }
    }
}
