#include "SerialPortWorker.h"

#include <QDebug>
#include <QSerialPort>

SerialPortWorker::SerialPortWorker(QObject *parent)
    : QObject(parent), m_serialPort(nullptr) {}

void SerialPortWorker::openSerialPort(const SerialPortInfo &info) {
    if (!m_serialPort) {
        m_serialPort = new QSerialPort(this);
        connect(m_serialPort, &QSerialPort::readyRead, this,
                &SerialPortWorker::readyRead);
    }

    m_serialPort->setPortName(info.name);
    m_serialPort->setBaudRate(info.baudRate);
    m_serialPort->setDataBits(info.dataBits);
    m_serialPort->setFlowControl(info.flowControl);
    m_serialPort->setParity(info.parity);
    m_serialPort->setStopBits(info.stopBits);
    auto result = m_serialPort->open(QIODevice::ReadWrite);
    result ? emit opened() : qDebug() << "Serial port cannot be opened";
}

void SerialPortWorker::closeSerialPort() {
    if (!m_serialPort) return;

    m_serialPort->close();
    emit closed();
}

void SerialPortWorker::readyRead() {
    QByteArray data = m_serialPort->readAll();
    qDebug() << "Receive data from serialPort:" << data.toHex();
    emit receiveMessage(data.toHex());
}

void SerialPortWorker::sendMessage(const QString &message, const bool &useHex) {
    if (!m_serialPort || !m_serialPort->isOpen()) {
        qDebug() << "Please open serial port first";
        return;
    }

    QByteArray data =
        useHex ? QByteArray::fromHex(message.toUtf8()) : message.toUtf8();
    m_serialPort->write(data);
    qDebug() << "Sent message = " << data;
}
