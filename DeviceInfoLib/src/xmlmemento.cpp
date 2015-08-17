#include "xmlmemento.h"

void XMLMemento::loadDeviceName()
{
    qDebug("Searching device name...");
    QDomNodeList e_list = m_xmlDoc.elementsByTagName("name");
    if(e_list.isEmpty()){
        qDebug("Error. File does'n contains device name");
        m_parent->setName("NoName");
    }
    else{
        QDomNode n = e_list.item(0);
        qDebug("OK.");
        m_parent->setName(n.toElement().text());
    }
}

void XMLMemento::loadDeviceSerialNumber()
{
    qDebug("Searching device serial number...");
    QDomNodeList e_list = m_xmlDoc.elementsByTagName("serialNumber");
    if(e_list.isEmpty()){
        qDebug("Error. File does'n contains serial number");
        m_parent->setSerialNum("А0000000");
    }
    else{
        QDomNode n = e_list.item(0);
        qDebug("OK.");
        m_parent->setSerialNum(n.toElement().text().toUtf8());
    }

}

void XMLMemento::loadDeviceNodes()
{
    qDebug("Searching device nodes...");
    QDomNodeList e_list = m_xmlDoc.elementsByTagName("node");
    if(!e_list.isEmpty()){
        QList<Node> nodeList;
        for(int i = 0; i < e_list.length(); i++){
            Node node;
            QDomElement element = e_list.item(i).toElement();
            QString number = element.attribute("number", QString("%1").arg(i));
            QString info = element.text();

            node.serialNum = number.toUInt();
            node.info = info;

            nodeList << node;
        }
        qDebug("OK. Found %d nodes.", nodeList.size());
        m_parent->setNodeList(nodeList);
    }
    else{
        qDebug("OK. Found 0 nodes.");
    }
}

void XMLMemento::loadDeviceMemRegs()
{
    qDebug("Searching memory regions...");
    QDomNodeList e_list = m_xmlDoc.elementsByTagName("region");
    if(!e_list.isEmpty()){
        QList<MemRegion> regionList;
        for(int i = 0; i < e_list.length(); i++){
            MemRegion region;
            QDomElement element = e_list.item(i).toElement();
            QString number = element.attribute("number", QString("%1").arg(i));
            QString startSector = element.attribute("startSector", QString("0"));
            QString endSector = element.attribute("endSector", QString("0"));
            QString pcmDevName = element.attribute("pcmDevName", QString("No Information"));
            QString name = element.text();

            region.setNumber(number.toUInt());
            region.setName(name);
            region.setStartSector(startSector.toUInt());
            region.setEndSector(endSector.toUInt());
            region.setPcmDevName(pcmDevName);

            regionList << region;
        }
        qDebug("OK. Found %d memory regions.", regionList.size());
        m_parent->setMemoryList(regionList);
    }
    else{
        qDebug("OK. Found 0 memory regions.");
    }
}

void XMLMemento::saveDeviceName(QDomElement *root)
{
    QDomElement e_name = m_xmlDoc.createElement("name");
    QDomText t_name = m_xmlDoc.createTextNode(m_parent->name());
    e_name.appendChild(t_name);
    root->appendChild(e_name);
}

void XMLMemento::saveDeviceSerialNumber(QDomElement *root)
{
    QDomElement e_serialNumber = m_xmlDoc.createElement("serialNumber");
    QDomText t_serialNumber = m_xmlDoc.createTextNode(m_parent->serialNum().toString());
    e_serialNumber.appendChild(t_serialNumber);
    root->appendChild(e_serialNumber);
}

void XMLMemento::saveDeviceNodes(QDomElement *root)
{
    QDomElement e_nodes = m_xmlDoc.createElement("nodes");
    for(int i = 0; i <  m_parent->nodeList().size(); i++)
    {
        QDomElement e_node = m_xmlDoc.createElement("node");
        e_node.setAttribute("number", m_parent->nodeList().at(i).serialNum);
        QDomText t_info = m_xmlDoc.createTextNode(m_parent->nodeList().at(i).info);
        e_node.appendChild(t_info);
        e_nodes.appendChild(e_node);
    }
    root->appendChild(e_nodes);
}

void XMLMemento::saveDeviceMemReg(QDomElement *root)
{
    QDomElement e_memoryRegiones = m_xmlDoc.createElement("memoryRegiones");
    for(int i = 0; i <  m_parent->memoryList().size(); i++)
    {
        QDomElement e_node = m_xmlDoc.createElement("region");
        e_node.setAttribute("number", m_parent->memoryList().at(i).number());
        e_node.setAttribute("startSector", m_parent->memoryList().at(i).startSector());
        e_node.setAttribute("endSector", m_parent->memoryList().at(i).endSector());
        e_node.setAttribute("pcmDevName", m_parent->memoryList().at(i).pcmDevName());
        QDomText t_name = m_xmlDoc.createTextNode(m_parent->memoryList().at(i).name());
        e_node.appendChild(t_name);
        e_memoryRegiones.appendChild(e_node);
    }
    root->appendChild(e_memoryRegiones);
}

XMLMemento::XMLMemento(Device *parent)
    : m_parent(parent)
{

}

void XMLMemento::loadFromXML(const QString &fileName)     // Загрузка устройства из XML
{
    qDebug("Load device from xml.");

    QFile file(fileName);

    if(!file.isOpen())
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug("Loading failed. Can't open XML file.");
            return;
        }

    if (!m_xmlDoc.setContent(&file)) {
        file.close();
        qDebug("Loading failed. Can't read XML file.");
        return;
    }
    file.close();

    loadDeviceName();
    loadDeviceSerialNumber();
    loadDeviceNodes();
    loadDeviceMemRegs();

}

void XMLMemento::saveInXML(const QString &fileName)       // Сохранение устройства в XML
{
    qDebug("Save device <%s> in xml...", m_parent->name().toLatin1().data());

    QFile file(fileName);
    if(!file.isOpen())
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
            qDebug("Saving failed. Can't open XML file.");
            return;
        }

    QDomElement root = m_xmlDoc.createElement("device");
    m_xmlDoc.appendChild(root);
    saveDeviceName(&root);
    saveDeviceSerialNumber(&root);
    saveDeviceNodes(&root);
    saveDeviceMemReg(&root);

    QString xml = m_xmlDoc.toString();

    QTextStream out(&file);
    out.seek(0);
    out <<"<?xml version=\"1.0\" encoding=\"windows-1251\"?>" << xml;
    file.close();

}
