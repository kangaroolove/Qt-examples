#pragma once

#include <QObject>
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

class QSerialPort;
class SerialPortWorker : public QObject
{
public:
    SerialPortWorker(QObject* parent = nullptr);
    ~SerialPortWorker();
    bool openSerialPort(const SerialPortInfo& info);
    void closeSerialPort();
public slots:
    void sendMessage(const QString& message, const bool& useHex);
    void receiveMessage();
private:
    QSerialPort* m_serialPort;
};