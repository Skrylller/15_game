import QtQuick 2.0

Rectangle {
    id: _counter;

    property string name: "";
    property int counter: 0;
    property int counterHeight: 50;

    height: counterHeight * 2;
    width: parent.width;

    color: "lightblue";

    border.color: "black";
    border.width: 1;

    radius: width / 20;

    Column{
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;

        spacing: 0;

        Text {
            id: _nameText;

            text: name + ": ";
            font{
                pointSize: Math.min(parent.width, parent.height) / 100 * 12;
                bold: true;
            }

        }
        Rectangle{
            id: _timerRect

            height: counterHeight;
            width: height;

            color: "steelblue";

            border.color: "black";
            border.width: 1;

            radius: width / 10;

            Text {
                id: _countText;
                anchors.centerIn: parent;

                text: counter;
                font{
                    pointSize: Math.min(parent.width, parent.height) / 100 * 32;
                    bold: true;
                }

            }
        }

    }
}
