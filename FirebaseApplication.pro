#QT += qml quick
QT += core
QT +=network
QT -= gui

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle


SOURCES += src/code/actionhandler.cpp \
    src/code/datasnapshot.cpp \
    src/code/firebase.cpp \
    src/code/json.cpp \
    src/code/main.cpp \

RESOURCES += \
    src.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    src/headers/actionhandler.h \
    src/headers/datasnapshot.h \
    src/headers/firebase.h \
    src/headers/json.h \
