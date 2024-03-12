#pragma once

#include <QLocalSocket>

class QDataStream;

class Worker : public QLocalSocket
{
    Q_OBJECT
public:
    Worker(QObject* parent = nullptr);
    ~Worker();
signals:
public slots:
    void sendMessage(const QByteArray &msg);
private slots:
    void readyToRead();
private:
    QDataStream* m_in;
};