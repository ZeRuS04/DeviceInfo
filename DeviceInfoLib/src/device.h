#ifndef ABSTRACTDEVICE_H
#define ABSTRACTDEVICE_H

#include <QVariant>
#include <QList>
#include <QMap>
#include <QRegExp>

#include "memregion.h"

/*
 *  Серийный номер устройства
 * */
typedef struct SerialNumber{
    QChar   prefix;     // Префикс, русская заглавная буква
    uint    index;      // 7-изначный индекс

    bool fromString(const QString &str){
        QRegExp rx("([А-Я]{1,1})(\\d{7})");

        int pos = rx.indexIn(str);
        if(pos == -1){
            qDebug("Error. Serial number is invalid.");
            return false;
        }
        prefix = rx.cap(1).at(0);
        index = rx.cap(2).toUInt();
        return true;
    }

    QString toString(){
        QString retVal = "%1%2";
        return retVal.arg(prefix).arg(index, 7, 10, QChar('0'));
    }
} SerialNumber;

/*
 *  Узел устройства
 * */
typedef struct Node{
    uint serialNum;     // Индекс узла
    QString info;       // Доп. информация об узле
    QString numToString(){
        QString retVal = "%1";
        return retVal.arg(serialNum, 7, 10, QChar('0'));
    }
} Node;


class XMLMemento;

/*
 *  Устройство
 * */

class Device
{
public:
    Device();
    Device(const QString &name, const QString &serialNum);
    Device(const QString &name, const QString &serialNum,
           const QList<Node> &nodeList, const QList<MemRegion> &memoryList);
    ~Device();


    //****** Setters and Getters *********//
    QString name() const;
    void setName(const QString &name);

    SerialNumber serialNum() const;
    void setSerialNum(const QString &serialNum);

    QList<Node> nodeList() const;
    void setNodeList(const QList<Node> &nodeList);

    QList<MemRegion> memoryList() const;
    void setMemoryList(const QList<MemRegion> &memoryList);

    QMap<QString, QVariant> otherParams() const;
    void setOtherParams(const QMap<QString, QVariant> &otherParams);


    void saveConfig(const QString &fileName);   // Сохранение в XML файл
    void loadConfig(const QString &fileName);   // Загрузка из XML файла

private:
    XMLMemento  *m_memento;                 // XML-Хранитель
    QString      m_devName;                 // Имя устройства
    SerialNumber m_serialNum;               // Серийный номер устройства
    QList<Node>  m_nodeList;                // Список узлов
    QList<MemRegion> m_memoryList;          // Список областей памяти
    QMap<QString, QVariant> m_otherParams;  // Другие параметры устройства(в формате "ключ-значение")

};


#endif // ABSTRACTDEVICE_H
