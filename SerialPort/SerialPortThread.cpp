#include "SerialPortThread.h"
#include <QSerialPort>
#include <QDebug>

SerialPortThread::SerialPortThread(QObject* parent)
    : QThread(parent)
    , m_quit(false)
    , m_serialPort(new QSerialPort(this))
    , m_readReady(false)
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortThread::receiveMessageFromSerialPort);
}

SerialPortThread::~SerialPortThread()
{
    m_quit = true;
    closeSerialPort();
}

void SerialPortThread::closeSerialPort()
{
    m_serialPort->close();
}

bool SerialPortThread::openSerialPort(const SerialPortInfo &info)
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

void SerialPortThread::sendMessage(const QString& message, const bool& useHex)
{
    if (!m_serialPort->isOpen())
    {
        qDebug()<<"Please open serial port first";
        return;
    }

    qDebug()<<"SerialPortThread --- sendMessage --- "<<message;

    QByteArray data = useHex ? QByteArray::fromHex(message.toLatin1()) : message.toUtf8();
    m_serialPort->write(data);
}

void SerialPortThread::run()
{
    while (!m_quit)
    {
        if (m_readReady)
        {
            m_readReady = false;
            QByteArray message = m_serialPort->readAll();
            // To handle package loss
            if (m_serialPort->waitForReadyRead(10))
            {
                message += m_serialPort->readAll();
                qDebug()<<message.size();
            }

            qDebug()<<"Receive:"<<message;
        }
    }
}

void SerialPortThread::receiveMessageFromSerialPort()
{
    qDebug()<<"Ready to read";
    m_readReady = true;
}
