#pragma once

#include <QThread>

class QLocalSocket;

class ClientWorker : public QThread
{
    Q_OBJECT
public:
    ClientWorker(QObject* parent = nullptr);
    void setQuit();
    void setServerName(const QString& name);
signals:
    void receiveMessage(const QString& msg);
public slots:
    void sendMessage(const QString& msg);
protected:
    void run() override;
private:
    QLocalSocket* m_socket;
    QString m_serverName;
    bool m_quit;
    static const int FPS;
};