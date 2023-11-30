import QtQuick 2.0

Rectangle {
    id: _root

    property string displayText: "";
    readonly property int defTextSize: 24;
    readonly property alias internalText: _numText;

    color: "lightgreen";

    border.color: "black";
    border.width: 1;

    radius: _root.width / 10;

    Text {
        id: _numText;
        anchors.centerIn: _root;

        text: _root.displayText;
        font{
            pointSize: Math.min(_root.width, _root.height) / 100 * 24;
            bold: true;
        }

    }
}
