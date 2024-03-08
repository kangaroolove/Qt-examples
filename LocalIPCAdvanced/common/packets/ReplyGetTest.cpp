#include "ReplyGetTest.h"

ReplyGetTest::ReplyGetTest(const QString &clientMessageId) :
    ReplyPacket(clientMessageId)
{
}

ReplyGetTest::~ReplyGetTest()
{

}

QJsonObject ReplyGetTest::generateData()
{
    QJsonObject object;
    object["value"] = 50;
    object["valueType"] = "int";
    return object;
}
