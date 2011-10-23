import QtQuick 1.0
import com.nokia.meego 1.0

PageStackWindow {
    id: rootWindow

    initialPage: Page {

        tools: ToolBarLayout {
            ButtonRow {
                style: TabButtonStyle { }
                TabIcon {
                    platformIconId: "toolbar-contact"
                }
                TabIcon {
                    platformIconId: "toolbar-list"
                }
                TabIcon {
                    platformIconId: "toolbar-new-chat"
                }
                TabIcon {
                    platformIconId: "toolbar-new-chat"
                }
                TabIcon {
                    platformIconId: "toolbar-settings"
                }
            }
        }

    }
}
