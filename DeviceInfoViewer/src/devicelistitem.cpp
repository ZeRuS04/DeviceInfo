#include "devicetlistitem.h"

DeviceListItem::DeviceListItem(Device *device)
    : m_device(device)
{
    setText(device->name());
}
Device *DeviceListItem::device() const
{
    return m_device;
}

void DeviceListItem::setDevice(Device *device)
{
    m_device = device;
}


