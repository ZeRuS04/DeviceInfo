#include "deviceviewer.h"
#include "ui_deviceviewer.h"
#include <QFileDialog>


DeviceViewer::DeviceViewer(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::DeviceViewer)
{
    ui->setupUi(this);
    ui->saveBtn->setDisabled(true);
    ui->loadBtn->setDisabled(true);
    ui->newBtn->setDisabled(true);
    ui->nameEdit->setDisabled(true);
    ui->serialNumEdit->setDisabled(true);
    connect(ui->saveBtn, &QPushButton::clicked, this, &DeviceViewer::saveConfig);
    connect(ui->loadBtn, &QPushButton::clicked, this, &DeviceViewer::loadConfig);
    connect(ui->newBtn, &QPushButton::clicked, this, &DeviceViewer::createNewConfig);
    connect(ui->devices, &QListWidget::itemClicked, this, &DeviceViewer::deviceClicked);
    connect(ui->nameEdit, &QLineEdit::textChanged, this, &DeviceViewer::changeName);
    connect(ui->serialNumEdit, &QLineEdit::textChanged, this, &DeviceViewer::changeSerialNumber);
    connect(ui->nodesTable, &QTableWidget::currentCellChanged, this, &DeviceViewer::changeNodes);
    connect(ui->memoryTable, &QTableWidget::currentCellChanged, this, &DeviceViewer::changeMemory);
}

DeviceViewer::~DeviceViewer()
{
    delete ui;
}

void DeviceViewer::addDevice(Device *dev)
{
    DeviceListItem* item = new DeviceListItem(dev);
    ui->devices->addItem(item);
}

void DeviceViewer::deviceClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)

    ui->saveBtn->setEnabled(true);
    ui->loadBtn->setEnabled(true);
    ui->newBtn->setEnabled(true);
    ui->nameEdit->setEnabled(true);
    ui->serialNumEdit->setEnabled(true);
    // TODO Сделать дполонительные параметры

    reloadDeviceView();

}

void DeviceViewer::reloadDeviceView()
{
    Device * device = dynamic_cast<DeviceListItem*>(ui->devices->currentItem())->device();
    ui->nameEdit->setText(device->name());
    ui->serialNumEdit->setText(device->serialNum().toString());

    ui->nodesTable->setRowCount(device->nodeList().size());
    for(int i = 0; i < device->nodeList().size(); i++){
        Node node = device->nodeList().at(i);
        QTableWidgetItem *number = new QTableWidgetItem(node.numToString());
        ui->nodesTable->setItem(i,0, number);
        QTableWidgetItem *info = new QTableWidgetItem(node.info);
        ui->nodesTable->setItem(i,1, info);
    }

    ui->memoryTable->setRowCount(device->memoryList().size());
    for(int i = 0; i < device->memoryList().size(); i++){
        MemRegion memory = device->memoryList().at(i);
        QTableWidgetItem *name = new QTableWidgetItem(memory.name());
        ui->memoryTable->setItem(i,0, name);
        QTableWidgetItem *number = new QTableWidgetItem(memory.numToString());
        ui->memoryTable->setItem(i,1, number);
        QTableWidgetItem *pcm = new QTableWidgetItem(memory.pcmDevName());
        ui->memoryTable->setItem(i,2, pcm);
        QTableWidgetItem *start = new QTableWidgetItem(QString("%1").arg(memory.startSector()));
        ui->memoryTable->setItem(i,3, start);
        QTableWidgetItem *end = new QTableWidgetItem(QString("%1").arg(memory.endSector()));
        ui->memoryTable->setItem(i,4, end);
    }
}

void DeviceViewer::saveConfig()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save File", "",
                                                    "XML files (*.xml)");
    Device * device = dynamic_cast<DeviceListItem*>(ui->devices->currentItem())->device();
    device->saveConfig(fileName);
}

void DeviceViewer::loadConfig()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Save File", "",
                                                    "XML files (*.xml)");
    Device * device = dynamic_cast<DeviceListItem*>(ui->devices->currentItem())->device();
    device->loadConfig(fileName);
    reloadDeviceView();
}

void DeviceViewer::createNewConfig()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save File", "",
                                                    "XML files (*.xml)");
    Device device;
    device.saveConfig(fileName);
}

void DeviceViewer::changeName(const QString &name)
{
    Device * device = dynamic_cast<DeviceListItem*>(ui->devices->currentItem())->device();
    device->setName(name);
}

void DeviceViewer::changeSerialNumber(const QString &num)
{
    Device * device = dynamic_cast<DeviceListItem*>(ui->devices->currentItem())->device();
    device->setSerialNum(num);
}

void DeviceViewer::changeNodes(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(previousColumn)
    Q_UNUSED(previousRow)
    // TODO Не работает changeNodes, исправить
    Device * device = dynamic_cast<DeviceListItem*>(ui->devices->currentItem())->device();
    switch (currentColumn) {
    case 0:
        device->nodeList()[currentRow].serialNum = ui->nodesTable->item(currentRow, currentColumn)->text().toUInt();
        break;
    case 1:
        device->nodeList()[currentRow].info = ui->nodesTable->item(currentRow, currentColumn)->text();
        break;
    default:
        break;
    }

}

void DeviceViewer::changeMemory(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(previousColumn)
    Q_UNUSED(previousRow)
    // TODO Не работает changeMemory, исправить
    Device * device = dynamic_cast<DeviceListItem*>(ui->devices->currentItem())->device();
    switch (currentColumn) {
    case 0:
        device->memoryList()[currentRow].setName(ui->nodesTable->item(currentRow, currentColumn)->text());
        break;
    case 1:
        device->memoryList()[currentRow].setNumber(ui->nodesTable->item(currentRow, currentColumn)->text().toUInt());
        break;
    case 2:
        device->memoryList()[currentRow].setPcmDevName(ui->nodesTable->item(currentRow, currentColumn)->text());
        break;
    case 3:
        device->memoryList()[currentRow].setStartSector(ui->nodesTable->item(currentRow, currentColumn)->text().toUInt());
        break;
    case 4:
        device->memoryList()[currentRow].setEndSector(ui->nodesTable->item(currentRow, currentColumn)->text().toUInt());
        break;
    default:
        break;
    }
}

