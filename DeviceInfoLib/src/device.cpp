#include "device.h"
#include "xmlmemento.h"
Device::Device()
    : m_memento(new XMLMemento(this))
    , m_devName("NoName")
{
    m_serialNum.fromString("А0000000");
}

Device::Device(const QString &devName, const QString &serialNum)
    : m_memento(new XMLMemento(this))
    , m_devName(devName)
{
    m_serialNum.fromString(serialNum);
}

Device::Device(const QString &devName, const QString &serialNum,
               const QList<Node> &nodeList, const QList<MemRegion> &memoryList)
    : m_memento(new XMLMemento(this))
    , m_devName(devName)
    , m_nodeList(nodeList)
    , m_memoryList(memoryList)
{
    m_serialNum.fromString(serialNum);
}

Device::~Device()
{
    delete m_memento;
}
QString Device::name() const
{
    return m_devName;
}

void Device::setName(const QString &devName)
{
    m_devName = devName;
}
SerialNumber Device::serialNum() const
{
    return m_serialNum;
}

void Device::setSerialNum(const QString &serialNum)
{
    // TODO Сделать проверку на возвращаемое значение
    m_serialNum.fromString(serialNum);
}
QList<Node> Device::nodeList() const
{
    return m_nodeList;
}

void Device::setNodeList(const QList<Node> &nodeList)
{
    m_nodeList = nodeList;
}
QList<MemRegion> Device::memoryList() const
{
    return m_memoryList;
}

void Device::setMemoryList(const QList<MemRegion> &memoryList)
{
    m_memoryList = memoryList;
}
QMap<QString, QVariant> Device::otherParams() const
{
    return m_otherParams;
}

void Device::setOtherParams(const QMap<QString, QVariant> &otherParams)
{
    m_otherParams = otherParams;
}

void Device::saveConfig(const QString &fileName)
{
    m_memento->saveInXML(fileName);
}

void Device::loadConfig(const QString &fileName)
{
    m_nodeList.clear();
    m_memoryList.clear();
    m_memento->loadFromXML(fileName);
}
