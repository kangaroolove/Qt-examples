#pragma once

#include <QLocalSocket>

class QDataStream;

class RequestResult
{
public:
    RequestResult() {}
    QString valueType;
    QVariant value;
};

class Worker : public QLocalSocket
{
    Q_OBJECT
public:
    Worker(QObject* parent = nullptr);
    ~Worker();
signals:
    void imageReceived(const QImage& image);
    void requestResultInserted(const QString& clientMessageId, const RequestResult& result);
    void eventLoopQuitted();
    void messageReceived(const QByteArray& msg);
public slots:
    void sendMessage(const QByteArray &msg);
private slots:
    void readyToRead();
private:
    bool isImagePacket(const QJsonDocument &document);

    QDataStream* m_in;
};