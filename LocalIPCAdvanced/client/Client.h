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
    
signals:
    void receiveMessage(const QByteArray& msg);
private slots:
    void readyToRead();
private:
    QDataStream* in;
    // shared variables
    std::unordered_map<QEventLoop*, QString> m_eventLoopMap;
};