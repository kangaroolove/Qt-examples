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
    PacketType getType() const;
    PacketType static getTypeFromBinaryData(const QByteArray& data);
    PacketType static getTypeFromJson(const QByteArray& data);
    QString static getMessageIdFromBinaryData(const QByteArray& data);
    QString static getMessageIdFromJson(const QByteArray& data);

    static const QString PACKET_TYPE;
    static const QString DATA;
    static const QString MESSAGE_ID;
protected:
    virtual QJsonObject generateData() = 0;
    void setMessageId(const QString& messageId);

    PacketType m_packetType;

private:
    QString generateMessageId();

    QString m_messageId;
};