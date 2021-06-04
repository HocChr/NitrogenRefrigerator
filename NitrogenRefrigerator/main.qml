import QtQuick 2.6
import QtQuick.Window 2.12
import QtQuick.Controls 2.15


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Nitrogen Refrigerator")
    id: munz

    Item {
        id: toolbar
        width: parent.width
        height: 75

        Button {
            id: button1
            anchors.left: parent.left; anchors.leftMargin: 5; y: 10; width: 60; height: 60
        }

        Button {
            anchors.left: button1.right; anchors.leftMargin: 5; y: 10; width: 60; height: 60
        }
    }

    Rectangle {
        id: refrigeratorView
        width: parent.width
        //height: parent.height - toolbar.height
        anchors.top: toolbar.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 5

        color: "Grey"
    }
}
