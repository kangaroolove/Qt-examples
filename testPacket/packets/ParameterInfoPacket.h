#pragma once

#include "Packet.h"
#include <QVariant>
#include <map>
#include <QString>

class ParameterInfoPacket : public Packet
{
public:
    ParameterInfoPacket(const std::map<QString, QVariant>& info);
    ParameterInfoPacket(const ParameterInfoPacket& packet);
    void printfSelf() override;
    static ParameterInfoPacket fromJson(const QByteArray& data);
protected:
    QJsonObject generateData() override;
private:
    std::map<QString, QVariant> m_parameterInfo;
};