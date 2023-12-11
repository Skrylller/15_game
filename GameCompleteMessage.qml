import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: window;

    property string messageText: "Test\ntext.";
    property string buttonText: "Перезапустить";
    property color messageColor: "lightgray";

    width: 200;
    height: 200;
    visible: GameController.gameComplete;
    flags: Qt.FramelessWindowHint;
    color: "#00000000";

    Rectangle{
        anchors.fill: parent;
        anchors.margins: 0;
        color: messageColor;
        border.color: "black";
        border.width: 1;
        radius: Math.min(width, height) / 20;

        ColumnLayout{

            anchors.fill: parent;
            anchors.margins: 20;
            spacing: 20;

            Text{
                id: _text;

                anchors.horizontalCenter: parent.horizontalCenter
                text: messageText;
                font{
                    pointSize: Math.min(parent.width, parent.height) / 100 * 12;
                    bold: true;
                }
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: buttonText
                font{
                    pointSize: Math.min(parent.width, parent.height) / 100 * 8;
                    bold: true;
                }
                onClicked: GameController.slotRestart();
            }
        }
    }
}
