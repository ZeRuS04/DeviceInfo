TEMPLATE = subdirs

SUBDIRS +=  DeviceInfoLib \
            DeviceInfoViewer

DeviceInfoViewer.depends = DeviceInfoLib
