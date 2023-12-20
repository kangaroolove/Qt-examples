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
    m_serialPort->close();
    m_quit = true;
}

void SerialPortThread::connectPort(const QString &portName, int waitTime)
{
    m_portName = portName;
    m_waitTime = waitTime;

    m_serialPort->setPortName(portName);
    qDebug()<<m_serialPort->error();
    m_serialPort->setBaudRate(QSerialPort::Baud19200);
    // m_serialPort->setDataBits(QSerialPort::Data8);
    // m_serialPort->setParity(QSerialPort::NoParity);
    // m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
    qDebug()<<m_serialPort->error();


    //qDebug()<<m_serialPort->readBufferSize();
    //m_serialPort->setReadBufferSize(4);


    connect(m_serialPort, &QSerialPort::errorOccurred, this, [this]{
        qDebug()<<m_serialPort->error();
        qDebug()<<m_serialPort->errorString();
    });

    connect(m_serialPort, &QSerialPort::readyRead, this, [this]{
        qDebug()<<"Ready to read";
        m_readReady = true;

        // QByteArray data = m_serialPort->readAll();
        // qDebug()<<data;
        // qDebug()<<data.size();
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
            if (m_serialPort->waitForReadyRead(10))
            {
                message += m_serialPort->readAll();
                qDebug()<<message.size();
            }

            qDebug()<<"Run receive"<<message;
        }

        // bool result = m_serialPort->waitForReadyRead(-1);
        // if (result)
        // {
        //     QByteArray message = m_serialPort->readAll();
        //     while (m_serialPort->waitForReadyRead(10))
        //         message += m_serialPort->readAll();
        //     qDebug()<<"Run receive"<<message;
        // }
        // else 
        // {
        //     qDebug()<<"error";
        // }
    }
}
