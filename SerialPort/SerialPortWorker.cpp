#include "SerialPortWorker.h"
#include <QSerialPort>
#include <QDebug>

SerialPortWorker::SerialPortWorker(QObject* parent)
    : QObject(parent)
    , m_serialPort(new QSerialPort(parent))
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortWorker::receiveMessageFromSerialPort);
}

SerialPortWorker::~SerialPortWorker()
{
    closeSerialPort();
    delete m_serialPort;
}

bool SerialPortWorker::openSerialPort(const SerialPortInfo &info)
{
    if (m_serialPort->isOpen())
    {
        qDebug()<<"SerialPort has opened";
        return false;
    }

    m_serialPort->setPortName(info.name);
    m_serialPort->setBaudRate(info.baudRate);
    m_serialPort->setDataBits(info.dataBits);
    m_serialPort->setFlowControl(info.flowControl);
    m_serialPort->setParity(info.parity);
    m_serialPort->setStopBits(info.stopBits);
    return m_serialPort->open(QIODevice::ReadWrite);
}

void SerialPortWorker::closeSerialPort()
{
    m_serialPort->close();
}

void SerialPortWorker::receiveMessageFromSerialPort()
{
    QByteArray data = m_serialPort->readAll();
    qDebug()<<"Receive data from serialPort:"<<data;
    emit receiveMessage(data);
}

void SerialPortWorker::sendMessage(const QString& message, const bool& useHex)
{
    if (!m_serialPort->isOpen())
    {
        qDebug()<<"Please open serial port first";
        return;
    }

    QByteArray data = useHex ? QByteArray::fromHex(message.toLatin1()) : message.toUtf8();
    m_serialPort->write(data);
}
