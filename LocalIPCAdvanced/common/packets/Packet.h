#pragma once

#include <QByteArray>
#include <QString>
class Packet
{
public:
    Packet();
    ~Packet();
    virtual QByteArray toJson() = 0;
    QString getMessageId();
private:
    void generateMessageId();

    QString m_messageId;
};