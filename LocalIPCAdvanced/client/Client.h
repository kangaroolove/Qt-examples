#pragma once

#include <QLocalSocket>
#include <map>
#include <QString>
#include <QImage>

class QDataStream;
class QEventLoop;
class QMutex;

class RequestResult
{
public:
    RequestResult() {}
    QString valueType;
    QVariant value;
};

class Client : public QLocalSocket
{
    Q_OBJECT
public:
    Client(QObject* parent = nullptr);
    ~Client();
    void insertRequestResult(const QString& messageId, const RequestResult& value);
    RequestResult getRequestResult(const QString& messageId);
signals:
    void receiveMessage(const QByteArray& msg);
    void quitEventloop();
    void imageReceived(QImage image);
public slots:
    void sendMessage(const QByteArray& msg);
    void connectServer();
private slots:
    void readyToRead();
protected:
    bool isImagePacket(const QJsonDocument& document);

    QDataStream* m_in;
    // key: messageId
    std::map<QString, RequestResult> m_resultMap;
};