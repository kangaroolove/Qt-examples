#pragma once

#include <QString>
#include <QSerialPort>

class SerialPortInfo
{
public:
    QString name;
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::FlowControl flowControl;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
};