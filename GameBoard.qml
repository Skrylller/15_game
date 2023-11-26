import QtQuick 2.0
import Game 1.0;

GridView {
    id: _root
    model: GameBoardModel {

    }

    cellWidth: _root.width / _root.model.m_sideSize
    cellHeight: _root.height / _root.model.m_sideSize

    delegate:Item{
        id: _backgroundDelegate

        readonly property int defSpacing: 5

        width: _root.cellWidth
        height: _root.cellHeight

        visible: display !== _root.model.m_cellNum


        MouseArea {
            anchors.fill: parent
            onClicked: {
                _root.model.move(index);
            }
        }

        Tile{
            internalText.text: display
            anchors.fill: _backgroundDelegate
            anchors.margins: Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * 5


        }
    }

}
