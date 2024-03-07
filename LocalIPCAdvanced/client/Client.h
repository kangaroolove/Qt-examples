#pragma once

#include <QLocalSocket>
#include <unordered_map>
#include <QString>

class QDataStream;
class QEventLoop;

class Client : public QLocalSocket
{
    Q_OBJECT
public:
    Client(QObject* parent = nullptr);
    ~Client();
    virtual void start() = 0;
    /**
     * @brief 
     * 
     * @param msg json data
     * @param messageId uuid
     */
    void sendMessage(const QByteArray& msg, const QString& messageId);
    void quitEventLoop(const QString& messageId);
    void insertResult(const QString& messageId, const QVariant& value);
    QVariant getResult(const QString& messageId);
signals:
    void receiveMessage(const QByteArray& msg);
private slots:
    void readyToRead();
private:
    QDataStream* in;
    // shared variables
    // key: messageId
    std::map<QString, QEventLoop*> m_eventLoopMap;
    // key: messageId
    std::map<QString, QVariant> m_resultMap;
};