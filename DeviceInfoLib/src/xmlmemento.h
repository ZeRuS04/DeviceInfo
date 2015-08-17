#ifndef XMLMEMENTO_H
#define XMLMEMENTO_H

#include <QDebug>
#include <QtXml>

#include "device.h"

class XMLMemento
{

    //=== Load ====
    void  loadDeviceName();
    void  loadDeviceSerialNumber();
    void  loadDeviceNodes();
    void  loadDeviceMemRegs();
    //=============

    //=== Save ====
    void  saveDeviceName(QDomElement *root);
    void  saveDeviceSerialNumber(QDomElement *root);
    void  saveDeviceNodes(QDomElement *root);
    void  saveDeviceMemReg(QDomElement *root);
    //TODO Сделать сохранение other param.

    //=============
public:
    XMLMemento(Device *parent);

    //=== XML. Создание, сохранение, загрузка. =========
    void createNewXML(QFile &file);

    void loadFromXML(const QString &fileName);

    void saveInXML(const QString &fileName);
    //==================================================

private:
    QDomDocument m_xmlDoc;                   //XML конфиг
    Device *m_parent;
};

#endif // XMLMEMENTO_H
