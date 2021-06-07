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
                       //onClicked: Qt.quit()
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

                ListView{
                    id: rackListLstView
                    anchors.fill: rackListItems
                    model: colorModel
                    delegate: nameDelegate

                    highlight: Rectangle {
                        color: 'grey'
                        Text {
                            anchors.centerIn: parent
                            text: 'Hello ' + colorModel.get(rackListLstView.currentIndex).name
                            color: 'white'
                        }
                    }

                    focus: true
                    onCurrentItemChanged: {
                        console.log(colorModel.get(currentIndex).name + ' selected');
                    }
                }

                Component{
                    id: nameDelegate

                    Rectangle{
                        id: itemDel

                        width: rackListItems.width
                        height: 90
                        color: "gainsboro"
                        border.color: "darkGray"
                        border.width: 1

                        Item {
                            anchors.fill: parent
                            Text {
                                id: delgateText1
                                color: "Black"
                                font.pixelSize: 24
                                anchors.verticalCenter: parent.verticalCenter
                                x: 20
                                text: name
                            }
                        }

                        MouseArea {
                            id: mouseAreaRacklList
                            anchors.fill: parent
                            onClicked: {
                                itemDel.state == 'clicked' ? itemDel.state = "" : itemDel.state = 'clicked';
                                rackListLstView.currentIndex = index
                            }
                        }

                        states: [
                                 State {
                                     name: "clicked"
                                     PropertyChanges { target: itemDel; color: "green" }
                                 }
                             ]
                    }
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
