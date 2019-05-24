import QtQuick.Window 2.11
import QtQuick.Layouts 1.11
import QtQuick.Controls 1.5
import QtQml.Models 2.11
import QtQuick 2.0
import Qt.labs.platform 1.0


Window {
    id: window
    property var colors:
    {
        'video'    : '#ffcf49',
        'audio'    : '#ff6464',
        'subtitle' : '#42adff',
        'other'    : '#888888'
    }

    visible: true
    width: 640
    height: 480
    title: 'FfmpegFileInfo'

    ColumnLayout {
        id: leftSide
        width: 300
        anchors.top:    parent.top
        anchors.bottom: parent.bottom
        anchors.left:   parent.left
        anchors.margins: 10
        Button {
            id: btnChangeDir
            Layout.fillWidth: true

            onClicked: folderDialog.open()
            text: {
                folderDialog.folder == undefined ? folderDialog.folder : "Chose folder"
            }
        }

        TreeView {
            id: filesView
            Layout.fillHeight: true
            Layout.fillWidth: true

            model: fileModel
            rootIndex: fileModel.rootIndex
            selection: fileModel.selection

            TableViewColumn {
                title: "Name"
                role: "fileName"
                movable: false
                resizable: false
            }
        }
    }
    Item {
        id: rightSide

        anchors.left:   leftSide.right
        anchors.bottom: parent.bottom
        anchors.top:    parent.top
        anchors.right:  parent.right
        anchors.margins: 10

        ColumnLayout {
            anchors.fill: parent
            visible: streamView.count > 0

            Text {
                text: {
                    var StrNumbers = fileModel.selectedFile.streamTypeNumbers
                    var typeNumbers = []

                    var type
                    for (type in StrNumbers) {
                        typeNumbers.push(StrNumbers[type] + " " + type)
                    }
                    typeNumbers = typeNumbers.join('; ')

                    return "Streams number: " + fileModel.selectedFile.streams.length + " (" + typeNumbers + ")"
                }
                font.bold: true
                font.pointSize: 11
            }
            Rectangle {
                Layout.fillHeight: true

                ListView {
                    id: streamView
                    anchors.fill: parent
                    model: fileModel.selectedFile.streams
                    delegate: streamDelegate
                }
            }
        }

        Text {
            visible: streamView.count == 0
            anchors.centerIn: parent
            color: "#888888"
            text: "N/A"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 37
        }
    }

    FolderDialog {
        id: folderDialog
        options: FolderDialog.ShowDirsOnly
        onAccepted: {

            var path = currentFolder.toString()

            // remove prefix "file:///"
            path = path.replace(/^(file:\/{3})/, "")

            fileModel.rootPath = path
        }
    }

    //============================ streamDelegate ============================
    Component {
        id: streamDelegate

        Item {
            height: 140
            width: 300

            Rectangle {
                anchors.fill: parent
                anchors.topMargin: 10
                color: {
                    var streamType = model.modelData.type
                    if (streamType in window.colors)
                        return window.colors[streamType]
                    else
                        return window.colors["other"]
                }

                ColumnLayout {
                    anchors.margins: 10
                    anchors.fill: parent
                    Text {
                        text: 'Stream #' + index
                        font.bold: true
                        font.pointSize: 10
                    }
                    Text {
                        text: 'Type: ' + model.modelData.type + '\n' + 'Codec: '
                              + model.modelData.codec
                        font.pointSize: 9
                    }
                    ListView {
                        header: Text {
                            text: 'Details:'
                            font.pointSize: 9
                        }
                        Layout.fillHeight: true
                        model: fileModel.selectedFile.streams[index].details
                        delegate: detailsDelegate
                    }
                }
            }
        }
    }

    //============================ detailsDelegate ============================
    Component {
        id: detailsDelegate
        Text {
            text: '  ' + model.modelData.property + ': ' + model.modelData.value
            font.pointSize: 8
        }
    }
}
