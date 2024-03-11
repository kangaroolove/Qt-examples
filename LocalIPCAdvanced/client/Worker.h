#pragma once

#include <QObject>

class QLocalSocket;
class QDataStream;

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(QObject* parent = nullptr);
    ~Worker();
signals:
    void messageReceived(const QString& msg);
public slots:
    void sendMessage(const QByteArray &msg);
    void connectToServer(const QString& name);
private slots:
    void readyRead();
private:
    QLocalSocket* m_localSocket;
    QDataStream* m_in;
};