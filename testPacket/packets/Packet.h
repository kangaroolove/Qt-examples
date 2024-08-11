#pragma once

#include <QByteArray>
#include <QString>
#include <QJsonObject>
#include <QObject>

enum class PacketType : unsigned int {
    UNKNOWN,
    FRAME,
    PARAMETER_INFO,
    REQUEST_UPDATE
};

class Packet : public QObject
{
    Q_OBJECT
public:
    Packet(QObject* parent = nullptr);
    QByteArray toJson();
    QString getMessageId() const;
    virtual QByteArray toBinary();
protected:
    virtual QJsonObject generateData() = 0;

    PacketType m_packetType;

private:
    void generateMessageId();

    QString m_messageId;
};