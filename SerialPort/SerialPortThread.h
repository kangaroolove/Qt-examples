#pragma once

#include <QThread>

class QSerialPort;

class SerialPortThread : public QThread
{
    Q_OBJECT
public:
    SerialPortThread(QObject* parent = nullptr);
    ~SerialPortThread();
    void connectPort(const QString& portName, int waitTime);
    void sendMessage(const QString& message);
signals:
    void receiveMessage(const QString& message);

protected:
    void run() override;

private:
    QString m_portName;
    int m_waitTime;
    QSerialPort* m_serialPort;
    bool m_quit;
    bool m_readReady;
};