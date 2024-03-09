#include "PacketFactory.h"
#include "ReplyGetTest.h"

PacketFactory::PacketFactory(QObject* parent)
    : QObject(parent)
{

}

PacketFactory::~PacketFactory()
{

}

Packet *PacketFactory::createReplyPacket(const QString &parameter, const QString &requestType, const QString &clientMessageId)
{
    if (requestType != "get")
        return nullptr;

    if (parameter == "test")
        return new ReplyGetTest(clientMessageId);

    return nullptr;
}
