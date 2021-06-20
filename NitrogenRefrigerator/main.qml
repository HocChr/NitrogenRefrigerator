import QtQuick 2.6
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

import nitrogenRefrigerator.qmlcomponets 1.0

Window {
    visible: true
    visibility: "Maximized"
    width: 1200
    height: 800

    property var stackList: null

    Component.onCompleted:{
        stackList = nitrogenRefrigerator.stacks
    }

    Rectangle
    {
        id: root
        anchors.fill: parent

        Rectangle{
            id: header
            width: parent.width
            height: 60

            Rectangle{
                id: saveButton
                height: parent.height
                width: 200
                anchors.left: parent.left
                color: "#1E1E1E"
                Text {
                    id: saveText
                    text: qsTr("Save")
                    font.pixelSize: 20
                    font.weight: Font.Medium
                    color: "White"
                    font.wordSpacing: 1
                    anchors.centerIn: parent
                }

                MouseArea {
                       property bool hoo: false
                       anchors.fill: parent
                       anchors.margins: -10
                       hoverEnabled: true         //this line will enable mouseArea.containsMouse
                       onHoveredChanged: {
                           if(hoo)
                           {
                               hoo = false
                               saveButton.color = "#1E1E1E"
                           }
                           else
                           {
                               hoo = true
                               saveButton.color = "Green"
                           }
                       }
                   }
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

                MouseArea {
                       property bool hoo: false
                       anchors.fill: parent
                       anchors.margins: -10
                       hoverEnabled: true         //this line will enable mouseArea.containsMouse
                       onClicked: Qt.quit()
                       onHoveredChanged: {
                           if(hoo)
                           {
                               hoo = false
                               closeButton.color = "#1E1E1E"
                           }
                           else
                           {
                               hoo = true
                               closeButton.color = "Green"
                           }
                       }
                   }
            }

        }

        Rectangle{
            id: rackListArea
            anchors.top: header.bottom
            anchors.bottom: root.bottom
            anchors.left: root.left
            width: 200

            Item {
                id: rackListHeader
                height: 50
                width: rackListArea.width

                Text {
                    id: rackHeader
                    text: qsTr("Racks")
                    font.pixelSize: 32
                    font.weight: Font.DemiBold
                    x: 5
                    //color: "gainsboro"
                    anchors.verticalCenter: rackListHeader.verticalCenter
                }

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
                    checkable: true
                    anchors.right: rackListHeader.right
                    anchors.margins: 5
                    anchors.verticalCenter: rackListHeader.verticalCenter
                }
            }

            Item {
                id: rackListItems
                anchors.top: rackListHeader.bottom
                anchors.bottom: rackListArea.bottom
                width: rackListArea.width

                ListModel{
                    id: colorModel

                    ListElement{
                        name: "Red"
                        value: 1
                    }

                    ListElement{
                        name: "Green"
                        value: 2
                    }

                    ListElement{
                        name: "Blue"
                        value: 3
                    }

                    ListElement{
                        name: "Gray"
                        value: 4
                    }

                    ListElement{
                        name: "Black"
                        value: 5
                    }

                    ListElement{
                        name: "Yellow"
                        value: 6
                    }
                }
                ListView {
                    id: list
                    anchors.fill: parent
                    model: stackList
                    delegate: Component {
                        Item {
                            id : bbb
                            width: parent.width
                            height: 40
                            property int index: modelData.index

                            Column {
                                anchors.verticalCenter: bbb.verticalCenter;
                                x: 20

                                Text {
                                    text: modelData.name;
                                    font.pixelSize: 18
                                    color: "black"
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked:{
                                    console.log(bbb.index)
                                    list.currentIndex = index
                                }
                            }
                        }
                    }
                    highlight: Rectangle {
                        color: 'green'
                    }
                    focus: true
                    onCurrentItemChanged: console.log(stackList[(list.currentIndex)].name + ' selected')
                }
            }
        }

        Rectangle{
            id: casetteListArea
            anchors.top: header.bottom
            anchors.bottom: root.bottom
            anchors.left: rackListArea.right
            width: 400
            color: "gainsboro"
        }

        Rectangle{
            id: casetteMatrixArea
            anchors.top: header.bottom
            anchors.bottom: root.bottom
            anchors.left: casetteListArea.right
            anchors.right: vialArea.left
            width: 400
            color: "gainsboro"
        }

        Rectangle{
            id: vialArea
            anchors.top: header.bottom
            anchors.bottom: root.bottom
            anchors.right:  root.right
            width: 400
            color: "gainsboro"
        }
    }
}
