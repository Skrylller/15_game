import QtQuick 2.0

Rectangle {
    id: _timer;

    readonly property int timerHeight: 60;

    height: timerHeight;
    width: parent.width;

    color: "lightblue";

    border.color: "black";
    border.width: 1;

    radius: _timer.width / 20;

    Row{

        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;

        Text {
            id: _minutesText;
            anchors.centerIn: _timer;

            text: "00";
            font{
                pointSize: Math.min(_timer.width, _timer.height) / 100 * 32;
                bold: true;
            }

        }

        Text {
            id: _spaceText;
            anchors.centerIn: _timer;

            text: " : ";
            font{
                pointSize: Math.min(_timer.width, _timer.height) / 100 * 32;
                bold: true;
            }

        }

        Text {
            id: _secondsText;
            anchors.centerIn: _timer;

            text: "00";
            font{
                pointSize: Math.min(_timer.width, _timer.height) / 100 * 32;
                bold: true;
            }

        }
    }
}
