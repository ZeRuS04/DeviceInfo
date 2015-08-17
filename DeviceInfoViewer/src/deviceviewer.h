#ifndef DEVICEVIEWER_H
#define DEVICEVIEWER_H

#include <QWidget>
#include <QTreeView>
#include "devicetlistitem.h"

namespace Ui {
class DeviceViewer;
}

class DeviceViewer : public QWidget
{
    Q_OBJECT

    void reloadDeviceView();
public:
    explicit DeviceViewer(QWidget *parent = 0);
    ~DeviceViewer();

    void addDevice(Device *dev);

public slots:
    void deviceClicked(QListWidgetItem* item);

    void saveConfig();
    void loadConfig();
    void createNewConfig();
    void changeName(const QString &name);
    void changeSerialNumber(const QString &num);
    void changeNodes(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void changeMemory(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::DeviceViewer *ui;
};

#endif // DEVICEVIEWER_H
