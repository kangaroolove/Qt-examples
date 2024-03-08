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
    virtual QJsonObject generateData() = 0;
    QString getMessageId();
private:
    void generateMessageId();

    QString m_messageId;
};