#include "serial.h"
#include <QSerialPortInfo>
#include <QDebug>

serial::serial(QObject *parent) : QObject(parent)
{
    getPorts();
}

void serial::getPorts()
{
    QStringList PortList;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        PortList.append(info.portName());
    }
    setPortsNames(PortList);
    // Check available ports evry 1000 ms
    QTimer::singleShot(1000, this, SLOT(getPorts()));
}

QString serial::getPortDescription(QString portName)
{
    QSerialPortInfo info(portName);
    qDebug() << "Serial Port " << portName << "Descrioption: " << info.description();
    return info.description();
}
