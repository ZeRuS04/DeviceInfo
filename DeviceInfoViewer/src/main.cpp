#include "deviceviewer.h"
#include <QApplication>
#include <device.h>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DeviceViewer w;

    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForLocale(codec);

    /****Add Test Devices ****/
    QList<MemRegion> memList;


    MemRegion r1("Region1", rand(),"EEPROM1",0,     256*256*14);
    MemRegion r2("Region2", rand(),"EEPROM2",256*256*14, 256*256*25);
    MemRegion r3("Region3", rand(),"EEPROM3",256*256*25, 256*256*40);
    MemRegion r4("Region4", rand(),"EEPROM1",256*256*40, 256*256*58);
    MemRegion r5("Region5", rand(),"EEPROM2",256*256*58, 256*256*80);
    MemRegion r6("Region6", rand(),"EEPROM3",256*256*80, 256*256*99);
    memList << r1 << r2 << r3 << r4 << r5 << r6;

    QList<Node> nodeList;
    for(int i = 0; i < 9; i++){
        Node n;
        n.serialNum = rand();
        n.info = QString("Something about node %1 of Device1").arg(i);
        nodeList << n;
    }
    Device dev1("Device1", "Т0000255", nodeList, memList);

    nodeList.clear();
    for(int i = 0; i < 6; i++){
        Node n;
        n.serialNum = rand();
        n.info = QString("Something about node %1 of Device2").arg(i);
        nodeList << n;
    }
    Device dev2("Device2", "И0000364", nodeList, memList);

    nodeList.clear();
    for(int i = 0; i < 3; i++){
        Node n;
        n.serialNum = rand();
        n.info = QString("Something about node %1 of Device3").arg(i);
        nodeList << n;
    }
    Device dev3("Device3", "Я0000982", nodeList, memList);

    w.addDevice(&dev1);
    w.addDevice(&dev2);
    w.addDevice(&dev3);

    /*************************/

    w.show();

    return a.exec();
}
