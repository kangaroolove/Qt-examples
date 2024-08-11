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
    QString getMessageId() const;
    PacketType getType() const;
    PacketType static getTypeFromJson(const QByteArray& data);
    virtual void printfSelf() = 0;
    virtual QByteArray toBinary();

    static const QString PACKET_TYPE;
    static const QString DATA;
    static const QString MESSAGE_ID;
protected:
    virtual QJsonObject generateData() = 0;
    static QString getMessageIdFromJson(const QByteArray& data);
    QByteArray toJson();

    PacketType m_packetType;
    QString m_messageId;
private:
    QString generateMessageId();
};