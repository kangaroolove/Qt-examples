#include "RequestGetTest.h"

RequestGetTest::RequestGetTest()
{

}

RequestGetTest::~RequestGetTest()
{

}

QJsonObject RequestGetTest::generateData()
{
    QJsonObject object;
    object["parameter"] = "test";
    object["requestType"] = "get";
    return object;
}
