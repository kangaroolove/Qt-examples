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

QJsonObject CommandPacket::generateData()
{
    QJsonObject object;
    object["command"] = m_command;

    return object;
}
