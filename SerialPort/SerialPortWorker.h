#pragma once

#include "Classes.h"
#include <QObject>

class QSerialPort;
class SerialPortWorker : public QObject
{
    Q_OBJECT
public:
    SerialPortWorker(QObject* parent = nullptr);
signals:
    void receiveMessage(const QString& message);
public slots:
    void sendMessage(const QString& message, const bool& useHex);
    void readyRead();
    void openSerialPort(const SerialPortInfo& info, bool& result);
    void closeSerialPort();
private:
    QSerialPort* m_serialPort;
};