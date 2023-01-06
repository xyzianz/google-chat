TEMPLATE = app
QT += gui webenginewidgets webenginequick widgets
SOURCES += google-chat.cpp
RESOURCES += google-chat.qrc
TARGET = google-chat

icons.path = $$(PREFIX)/share/icons/hicolor/
icons.files += icons/google-chat/16x16 icons/google-chat/32x32 icons/google-chat/48x48 icons/google-chat/64x64 icons/google-chat/96x96 icons/google-chat/128x128 icons/google-chat/160x160 icons/google-chat/192x192 icons/google-chat/256x256 icons/google-chat/512x512 icons/google-chat/scalable

target.path = $$(PREFIX)/bin/

desktop.path = $$(PREFIX)/share/applications/
desktop.files = *.desktop

INSTALLS += icons target desktop
