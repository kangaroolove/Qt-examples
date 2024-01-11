#pragma once

#include "Classes.h"
#include <QThread>

class QSerialPort;
class SerialPortThread : public QThread
{
    Q_OBJECT
public:
    SerialPortThread(QObject* parent = nullptr);
    ~SerialPortThread();
    bool openSerialPort(const SerialPortInfo &info);
    void closeSerialPort();
    void sendMessage(const QString& message, const bool& useHex);
signals:
    void receiveMessage(const QString& message);
protected:
    void run() override;
private slots:
    void receiveMessageFromSerialPort();
    void setUpReadyToRead();

private:
    QSerialPort* m_serialPort;
    bool m_quit;
    bool m_readReady;
    bool m_isFirstTimeReceiveMessage;
};