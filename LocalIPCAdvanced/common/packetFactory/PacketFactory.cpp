#include "PacketFactory.h"
#include "ReplyGetTest.h"

PacketFactory::PacketFactory(QObject* parent)
    : QObject(parent)
{

}

PacketFactory::~PacketFactory()
{

}

Packet *PacketFactory::createReplyPacket(const QString &parameter, const QString &clientMessageId)
{
    if (parameter == "test")
        return new ReplyGetTest(clientMessageId);

    return nullptr;
}
