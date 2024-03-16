#include "CommandPacket.h"

CommandPacket::CommandPacket(const QString& command) :
    m_command(command)
{

}

CommandPacket::~CommandPacket()
{

}

QJsonObject CommandPacket::generateData()
{
    QJsonObject object;
    object["command"] = m_command;

    return object;
}
