import QtQuick 2.0

GridView {
    id: _root

    property int spacing: 5

    model: 15

    cellWidth: _root.width / 4
    cellHeight: _root.height / 4

    delegate:Item{
        id: _backgroundDelegate

        width: _root.cellWidth
        height: _root.cellHeight

        Tile{
            internalText.text: display
            anchors.fill: _backgroundDelegate
            anchors.margins: Math.min(_backgroundDelegate.width, _backgroundDelegate.height) / 100 * spacing
        }
    }

}
