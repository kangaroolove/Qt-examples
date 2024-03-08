#include "ReplyGetTest.h"

ReplyGetTest::ReplyGetTest()
{

}

ReplyGetTest::~ReplyGetTest()
{

}

QJsonObject ReplyGetTest::generateData()
{
    QJsonObject object;
    object["value"] = "50";
    object["valueType"] = "int";
    return object;
}
