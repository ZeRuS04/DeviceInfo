#-------------------------------------------------
#
# Project created by QtCreator 2015-08-15T22:36:03
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeviceInfoViewer
TEMPLATE = app


SOURCES += src/main.cpp\
        src/deviceviewer.cpp \
    src/devicelistitem.cpp
#    src/treeitem.cpp \
#    src/treemodel.cpp

HEADERS  += src/deviceviewer.h \
    src/devicelistitem.h
#    src/treeitem.h \
#    src/treemodel.h

FORMS    += deviceviewer.ui


unix|win32: LIBS += -L$$OUT_PWD/../bin/ -lDeviceInfoLib

INCLUDEPATH += $$PWD/../DeviceInfoLib/src
DEPENDPATH += $$PWD/../DeviceInfoLib/src

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../bin/DeviceInfoLib.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../bin/libDeviceInfoLib.a
