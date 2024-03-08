#include "Packet.h"
#include <QUuid>

Packet::Packet()
{
    generateMessageId();
}

Packet::~Packet()
{

}

QString Packet::getMessageId()
{
    return m_messageId;
}

void Packet::generateMessageId()
{
    m_messageId = QUuid::createUuid().toString();
}
