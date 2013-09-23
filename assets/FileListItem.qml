import bb.cascades 1.2

Container {
    id: list_item
    
    property int icon_border: 14
    property int icon_size: 82
    property int status_size: 90
        
    layout:DockLayout {}
    
    Container {
        verticalAlignment: VerticalAlignment.Center
        horizontalAlignment: HorizontalAlignment.Left

        leftPadding: icon_border
        rightPadding: icon_border
        topPadding: icon_border
        bottomPadding: icon_border
        
        ImageView{
            scalingMethod: ScalingMethod.AspectFill
            preferredHeight: icon_size
            preferredWidth: icon_size
            image: ListItemData.icon
        }        
    }
    
    Container {
        verticalAlignment: VerticalAlignment.Center
        horizontalAlignment: HorizontalAlignment.Fill
        
        leftPadding: icon_border*2 + icon_size
        preferredHeight: icon_size + icon_border/2
        
        layout: DockLayout {}

        Label{
            verticalAlignment: VerticalAlignment.Top
            text: ListItemData.name            
            textStyle {
                fontSize: FontSize.PercentageValue = 110
            }                         
        }
        
        Label{
            verticalAlignment: VerticalAlignment.Bottom
            text: ListItemData.date
            textStyle {
                fontSize: FontSize.PercentageValue = 90
                color: Color.DarkGray
            }                         
        } 
    }
    
    Container {
        verticalAlignment: VerticalAlignment.Center
        horizontalAlignment: HorizontalAlignment.Right
                
        Label{
            preferredWidth: status_size
            text: ListItemData.size                            
            textStyle {
                fontSize: FontSize.PercentageValue = 74
                color: Color.DarkGray
            }                         
        } 
    }
    
    Divider {
    }

	function setHighlight(highlighted) {
		if (highlighted) {
		    list_item.background = Color.create("#18AFE2");
		} else {
		    list_item.background = Color.create("#018AFE2");
		}
	}
    
    ListItem.onActivationChanged: {
        setHighlight(ListItem.active);
    }
}
