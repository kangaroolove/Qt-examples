#include "ReplyGetTest.h"
#include <QVariant>

ReplyGetTest::ReplyGetTest(const QString& clientMessageId) :
    ReplyPacket("test", "get", clientMessageId)
{

}

ReplyGetTest::~ReplyGetTest()
{

}

QVariant ReplyGetTest::getValue()
{
    return QVariant(10);
}

QString ReplyGetTest::getValueType()
{
    return "int";
}
