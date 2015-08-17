QT       += xml

QT       -= gui

# каталог, куда ложить результирующий исполняемый файл
DESTDIR = $$PWD/../bin

# промежуточные файлы, созданные moc
MOC_DIR = moc

# объектные файлы
OBJECTS_DIR = obj

# промежуточные файлы, созданные компилятором
# ресурсов Qt (rcc)
RCC_DIR = rcc

# промежуточные файлы, созданные компилятором
# файлов форм (.ui) Qt (uic)
UI_DIR = uic

TARGET = DeviceInfoLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    src/memregion.cpp \
    src/device.cpp \
    src/xmlmemento.cpp

HEADERS += \
    src/memregion.h \
    src/device.h \
    src/xmlmemento.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
