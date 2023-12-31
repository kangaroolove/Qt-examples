#include "SerialPortThread.h"
#include <QSerialPort>
#include <QDebug>

SerialPortThread::SerialPortThread(QObject* parent)
    : QThread(parent)
    , m_waitTime(0)
    , m_quit(false)
    , m_serialPort(new QSerialPort(this))
    , m_readReady(false)
{

}

SerialPortThread::~SerialPortThread()
{
    m_quit = true;
    m_serialPort->close();
}

void SerialPortThread::connectPort(const QString &portName, int waitTime)
{
    m_portName = portName;
    m_waitTime = waitTime;

    m_serialPort->setPortName(portName);
    qDebug()<<m_serialPort->error();
    m_serialPort->setBaudRate(QSerialPort::Baud19200);
    qDebug()<<m_serialPort->error();

    connect(m_serialPort, &QSerialPort::errorOccurred, this, [this]{
        qDebug()<<m_serialPort->error();
        qDebug()<<m_serialPort->errorString();
    });

    connect(m_serialPort, &QSerialPort::readyRead, this, [this]{
        qDebug()<<"Ready to read";
        m_readReady = true;
    });
    
    if (!m_serialPort->open(QIODevice::ReadWrite))
    {
        qDebug()<<"Cannot open "<<m_portName;
        return;
    }

    if (!this->isRunning())
        start();
}

void SerialPortThread::sendMessage(const QString &message)
{
    m_serialPort->write(QByteArray::fromHex(message.toLatin1()));
    m_serialPort->flush();
    qDebug()<<"Write data:"<<message<<" successfully";
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
