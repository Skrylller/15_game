import QtQuick 2.0
import Game 1.0;


GridView {
    id: _root
    model: GameBoardModel {

    }

    cellWidth: _root.width / _root.model.m_sideSize;
    cellHeight: _root.height / _root.model.m_sideSize;

    delegate:Item{
        id: _backgroundDelegate;

        readonly property int defSpacing: 5;

        readonly property int animLenght: 200;

        width: _root.cellWidth;
        height: _root.cellHeight;

        visible: display !== _root.model.m_cellNum;


        MouseArea {
            anchors.fill: parent;
            onClicked: {
                _root.model.move(index);
            }
        }

        Tile{
            id: _tile;
            internalText.text: display;
            anchors.fill: _backgroundDelegate;
            anchors.margins: Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 5;
        }

        ParallelAnimation{
            id: _move_anim;
            running: _root.model.isAnimRun && (_root.model.selectedCell === display);

            NumberAnimation {
                target: _tile;
                property: "anchors.leftMargin";
                duration: animLenght;
                from: _root.model.horizontalAnimDirection * _backgroundDelegate.width + Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 5;
                to: Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 5;
            }
            NumberAnimation {
                target: _tile;
                property: "anchors.rightMargin";
                duration: animLenght;
                from: -_root.model.horizontalAnimDirection * _backgroundDelegate.width + Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 5;
                to: Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 5;
            }
            NumberAnimation {
                target: _tile;
                property: "anchors.topMargin";
                duration: animLenght;
                from: _root.model.verticalAnimDirection * _backgroundDelegate.height + Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 5;
                to: Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 5;
            }
            NumberAnimation {
                target: _tile;
                property: "anchors.bottomMargin";
                duration: animLenght;
                from: -_root.model.verticalAnimDirection * _backgroundDelegate.height + Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 5;
                to: Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 5;
            }
/*
            SequentialAnimation{
                NumberAnimation{
                    target: _tile;
                    property: "anchors.margins";
                    duration: animLenght / 2;
                    from: Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 5;
                    to: Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 3;
                }

                NumberAnimation{
                    target: _tile;
                    property: "anchors.margins";
                    duration: animLenght / 2;
                    from: Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 3;
                    to: Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 5;
                }
            }*/
        }

    }

}
