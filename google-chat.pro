TEMPLATE = app
QT += gui webenginewidgets webenginequick widgets
SOURCES += google-chat.cpp
RESOURCES += google-chat.qrc
TARGET = google-chat

icons.path = $$(PREFIX)/share/icons/hicolor/
icons.files = icons/google-chat/*

target.path = $$(PREFIX)/bin/

desktop.path = $$(PREFIX)/share/applications/
desktop.files = *.desktop

INSTALLS += icons target desktop
