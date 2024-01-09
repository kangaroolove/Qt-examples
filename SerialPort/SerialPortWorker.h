#pragma once

#include "Classes.h"
#include <QObject>

class QSerialPort;
class SerialPortWorker : public QObject
{
    Q_OBJECT
public:
    SerialPortWorker(QObject* parent = nullptr);
    ~SerialPortWorker();
    void closeSerialPort();
signals:
    void receiveMessage(const QString& message);
public slots:
    void sendMessage(const QString& message, const bool& useHex);
    void receiveMessageFromSerialPort();
    bool openSerialPort(const SerialPortInfo& info);
private:
    QSerialPort* m_serialPort;
};