
import bb.cascades 1.0

Page {
    Container {
        background: back.imagePaint
        attachedObjects: [
            ImagePaintDefinition {
                id: back
                repeatPattern: RepeatPattern.XY
                imageSource: "asset:///images/background.amd"
            }
        ]
                
        layout: DockLayout {}
        
        Container {
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center
            
            layout: StackLayout {}
            
            Button {
                id: buttonLocal
                
                text: qsTr("Load local files")
                
                onClicked: {
                    _app.loadLocalFiles()
                    visible = false
                    buttonRemote.visible = false
                    listView.visible = true
                }
            }
            
            Button {
                id: buttonRemote
                            
                text: qsTr("Load remote files")
                
                onClicked: {
                    _app.loadRemoteFiles()
                    visible = false
                    buttonLocal.visible = false
                    listView.visible = true
                }
            }
        }

        ListView {
            id: listView

            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill

            visible: false

            dataModel: _app.model

            listItemComponents: ListItemComponent {
                type: ""
                FileListItem {}
            }
        }
    }
}
