#include "memregion.h"

MemRegion::MemRegion()
    : m_name("")
    , m_number(0)
    , m_pcmDevName("")
    , m_startSector(0)
    , m_endSector(0)
    , m_isReady(false)
{

}

MemRegion::MemRegion(const QString &name, const uint &number, const QString &pcmDevName,
                     const uint &startSector, const uint &endSector)
    : m_name(name)
    , m_number(number)
    , m_pcmDevName(pcmDevName)
    , m_startSector(0)
    , m_endSector(0)
    , m_isReady(false)
{
    if((endSector-startSector > 0) && ((endSector-startSector)%256 == 0)){
        m_startSector = startSector;
        m_endSector = endSector;
        m_isReady = true;
    }

}
QString MemRegion::name() const
{
    return m_name;
}

void MemRegion::setName(const QString &name)
{
    m_name = name;
}
uint MemRegion::number() const
{
    return m_number;
}

QString MemRegion::numToString() const
{
    return QString("%1").arg(m_number, 7, 10, QChar('0'));
}

void MemRegion::setNumber(const uint &number)
{
    m_number = number;
}
QString MemRegion::pcmDevName() const
{
    return m_pcmDevName;
}

void MemRegion::setPcmDevName(const QString &pcmDevName)
{
    m_pcmDevName = pcmDevName;
}
uint MemRegion::startSector() const
{
    return m_startSector;
}

void MemRegion::setStartSector(const uint &startSector)
{
    m_startSector = startSector;
}
uint MemRegion::endSector() const
{
    return m_endSector;
}

void MemRegion::setEndSector(const uint &endSector)
{
    m_endSector = endSector;
}






