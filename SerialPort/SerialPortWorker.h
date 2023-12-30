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
    Q_OBJECT
public:
    SerialPortWorker(QObject* parent = nullptr);
    ~SerialPortWorker();
    bool openSerialPort(const SerialPortInfo& info);
    void closeSerialPort();
signals:
    void receiveMessage(const QString& message);
public slots:
    void sendMessage(const QString& message, const bool& useHex);
    void receiveMessageFromSerialPort();
private:
    QSerialPort* m_serialPort;
};