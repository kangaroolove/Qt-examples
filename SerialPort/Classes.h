#pragma once

#include <QSerialPort>
#include <QString>

class SerialPortInfo {
public:
  QString name;
  QSerialPort::BaudRate baudRate;
  QSerialPort::DataBits dataBits;
  QSerialPort::FlowControl flowControl;
  QSerialPort::Parity parity;
  QSerialPort::StopBits stopBits;
};
Q_DECLARE_METATYPE(SerialPortInfo)