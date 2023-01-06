import QtQuick
import QtQuick.Window
import QtWebEngine
import Qt.labs.platform

Window {
    width: 480
    height: 960
    visible: true
    id: mainwindow

    onClosing: {
    	close.accepted = false
    	mainwindow.hide()
    }

    Shortcut {
        sequence: StandardKey.Quit
        context: Qt.ApplicationShortcut
        onActivated: Qt.exit(0)
    }

    WebEngineView {
        anchors.fill: parent
        url: "https://mail.google.com/chat/u/0"
        onLoadingChanged: {}
        onLinkHovered: {}
        
        onNewWindowRequested: function(request) {
            if (request.userInitiated) {
                Qt.openUrlExternally(request.requestedUrl)
            }
        }

        onNavigationRequested: function(request) {
            if (request.navigationType === WebEngineNavigationRequest.LinkClickedNavigation) {
                Qt.openUrlExternally(request.url)
                request.reject()
            }
        }

    }

    SystemTrayIcon {
        visible: true
        icon.name: "google-chat"
        
        onActivated: {
            if (mainwindow.visible) {
                mainwindow.hide()
            } else {
                mainwindow.show()
                mainwindow.raise()
                mainwindow.requestActivate()
            }
        }

        menu: Menu {
            MenuItem {
                text: qsTr("Quit")
                onTriggered: Qt.exit(0)
            }
        }
    }

}

