#pragma once

#include <QByteArray>
#include <QString>
#include <QJsonObject>
#include <QObject>
class Packet : public QObject
{
    Q_OBJECT
public:
    Packet(QObject* parent = nullptr);
    ~Packet();
    QByteArray toJson();
    QString getMessageId() const;
    virtual QByteArray toBinary();
protected:
    virtual QJsonObject generateData() = 0;

    QString m_packetType;
    QString m_messageId;
private:
    void generateMessageId();
};