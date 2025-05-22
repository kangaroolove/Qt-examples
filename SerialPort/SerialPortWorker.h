#pragma once

#include "Classes.h"
#include <QObject>
#include <memory>

class QSerialPort;
class SerialPortWorker : public QObject {
    Q_OBJECT
public:
    SerialPortWorker(QObject *parent = nullptr);
    bool isOpen() const;
signals:
    void receiveMessage(const QString &message);
    void opened();
    void closed();
public slots:
    void sendMessage(const QString &message, const bool &useHex);
    void readyRead();
    void openSerialPort(const SerialPortInfo &info);
    void closeSerialPort();

private:
    std::unique_ptr<QSerialPort> m_serialPort;
};