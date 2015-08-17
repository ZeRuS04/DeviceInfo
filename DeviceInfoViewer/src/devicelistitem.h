#ifndef DEVICETLISTITEM_H
#define DEVICETLISTITEM_H

#include <QListWidgetItem>
#include "device.h"

class DeviceListItem : public QListWidgetItem
{
public:
    DeviceListItem(Device *device);

    Device *device() const;
    void setDevice(Device *device);
private:
    Device *m_device;
};

#endif // DEVICETLISTITEM_H
