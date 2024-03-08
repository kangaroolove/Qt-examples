#pragma once

#include <QByteArray>
#include <QString>
#include <QJsonObject>
class Packet
{
public:
    Packet();
    ~Packet();
    virtual QByteArray toJson() = 0;
    QString getMessageId();
protected:
    virtual QJsonObject generateData() = 0;
private:
    void generateMessageId();

    QString m_messageId;
};