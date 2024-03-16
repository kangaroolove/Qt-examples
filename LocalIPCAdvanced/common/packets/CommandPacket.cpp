#include "CommandPacket.h"

CommandPacket::CommandPacket(const QString& command) :
    m_command(command)
{

}

CommandPacket::~CommandPacket()
{

}

QString CommandPacket::getCommand() const
{   
    return m_command;
}

CommandPacket CommandPacket::fromJson(const QJsonObject &object)
{
     return CommandPacket(object["data"].toObject()["command"].toString());
}

QJsonObject CommandPacket::generateData()
{
    QJsonObject object;
    object["command"] = m_command;

    return object;
}
