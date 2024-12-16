#include "SerialPortWorker.h"
#include <QDebug>
#include <QEventLoop>
#include <QSerialPort>

SerialPortWorker::SerialPortWorker(QObject *parent)
    : QObject(parent), m_serialPort(nullptr) {}

bool SerialPortWorker::isOpen() const {
  if (!m_serialPort)
    return false;

  return m_serialPort->isOpen();
}

void SerialPortWorker::openSerialPort(const SerialPortInfo &info) {
  m_serialPort = std::make_unique<QSerialPort>(new QSerialPort(this));

  QEventLoop loop;
  connect(m_serialPort.get(), &QSerialPort::readyRead, this,
          &SerialPortWorker::readyRead);
  connect(m_serialPort.get(), &QSerialPort::errorOccurred, &loop,
          &QEventLoop::quit);
  connect(m_serialPort.get(), &SerialPortWorker::destroyed, &loop,
          &QEventLoop::quit);

  m_serialPort->setPortName(info.name);
  m_serialPort->setBaudRate(info.baudRate);
  m_serialPort->setDataBits(info.dataBits);
  m_serialPort->setFlowControl(info.flowControl);
  m_serialPort->setParity(info.parity);
  m_serialPort->setStopBits(info.stopBits);
  auto result = m_serialPort->open(QIODevice::ReadWrite);
  if (result)
    emit opened();

  qDebug() << "result = " << result;
  loop.exec();

  qDebug() << "loop quitted";
}

void SerialPortWorker::closeSerialPort() {
  if (!m_serialPort)
    return;

  m_serialPort->close();
  m_serialPort.reset();
  emit closed();
}

void SerialPortWorker::readyRead() {
  QByteArray data = m_serialPort->readAll();
  qDebug() << "Receive data from serialPort:" << data;
  emit receiveMessage(data);
}

void SerialPortWorker::sendMessage(const QString &message, const bool &useHex) {
  if (!isOpen()) {
    qDebug() << "Please open serial port first";
    return;
  }

  QByteArray data =
      useHex ? QByteArray::fromHex(message.toLatin1()) : message.toUtf8();
  m_serialPort->write(data);

  qDebug() << "Sent message = " << message;
}
