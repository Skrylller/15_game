import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: _root
    visible: true;
    width: 640;
    height: 480;
    title: qsTr("15 to match");

    Rectangle{
        width: _root.width;
        height: _root.height;
        color: "lightblue";

        Rectangle{
            id : _rect;
            width: 100;
            height: 100;
            color: "green";

            /*
            NumberAnimation on x {
                from: 0; to: 150;
                duration: 1000
            }*/
        }

        GameBoard{
            anchors.fill: parent;
        }
    }

    PropertyAnimation{
        target: _rect;
        properties: "width, height";
        from: 0; to: 150;
        duration: 1000;
        running: true;
    }
}
