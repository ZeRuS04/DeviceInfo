#ifndef MEMREGION_H
#define MEMREGION_H

#include <QString>
/*
 *  Область памяти
 * */
class MemRegion
{
public:
    MemRegion();
    MemRegion(const QString &name, const uint &number, const QString &pcmDevName,
              const uint &startSector, const uint &endSector);

    //****** Setters and Getters *********//
    QString name() const;
    void setName(const QString &name);

    uint number() const;
    QString numToString() const;
    void setNumber(const uint &number);

    QString pcmDevName() const;
    void setPcmDevName(const QString &pcmDevName);

    uint startSector() const;
    void setStartSector(const uint &startSector);

    uint endSector() const;
    void setEndSector(const uint &endSector);

private:
    QString m_name;         // Имя области памяти
    uint    m_number;       // Порядковый номер
    QString m_pcmDevName;   // Название платы к которой отностися область памяти
    uint    m_startSector;  // Номер начального сектора
    uint    m_endSector;    // Номер конечного сектора

    bool    m_isReady;      // Проверка на готовность к работе
};

#endif // MEMREGION_H
