import QtQuick 2.6
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    visible: true
    visibility: "Maximized"
    width: 1200
    height: 800

    Rectangle
    {
        id: root
        anchors.fill: parent

        Rectangle{
            id: header
            width: parent.width
            height: 60

            Button{
                id: filterButton
                Image {
                    anchors.fill: parent
                    anchors.margins: 5
                    source: "qrc:/Icons/filter_icon.png"
                    fillMode: Image.Stretch
                }
                width: 30
                height: 30
                x: 15;
                anchors.verticalCenter: header.verticalCenter
                ToolTip.visible: hovered
                ToolTip.text: "Filter"
                checkable: true
            }

            Text {
                id: filterText
                text: qsTr("Filter")
                x: 53
                anchors.verticalCenter: header.verticalCenter
                font.pixelSize: 20
                font.weight: Font.Medium
                font.wordSpacing: 1
            }

            Text {
                id: title
                text: qsTr("Nitrogen Refrigerator")
                anchors.centerIn: header
                font.pixelSize: 28
                font.weight: Font.DemiBold
                font.wordSpacing: 1
            }

            Rectangle{
                id: closeButton
                height: parent.height
                width: 200
                anchors.right: parent.right
                color: "#1E1E1E"
                Text {
                    id: closeText
                    text: qsTr("Close Application")
                    font.pixelSize: 20
                    font.weight: Font.Medium
                    color: "White"
                    font.wordSpacing: 1
                    anchors.centerIn: parent
                }
            }

        }

        Rectangle{
            id: rackListArea
            anchors.top: header.bottom
            anchors.bottom: root.bottom
            anchors.left: root.left
            border.color: "black"
            border.width: 1
            width: 200
        }

        Rectangle{
            id: casetteListArea
            anchors.top: header.bottom
            anchors.bottom: root.bottom
            anchors.left: rackListArea.right
            border.color: "black"
            border.width: 1
            width: 400
        }

        Rectangle{
            id: casetteMatrixArea
            anchors.top: header.bottom
            anchors.bottom: root.bottom
            anchors.left: casetteListArea.right
            anchors.right: vialArea.left
            border.color: "black"
            width: 400
        }

        Rectangle{
            id: vialArea
            anchors.top: header.bottom
            anchors.bottom: root.bottom
            anchors.right:  root.right
            border.color: "black"
            border.width: 1
            width: 400
        }
    }
}
