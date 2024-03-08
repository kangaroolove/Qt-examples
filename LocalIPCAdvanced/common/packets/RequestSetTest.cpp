#include "RequestSetTest.h"

RequestSetTest::RequestSetTest()
{

}

RequestSetTest::~RequestSetTest()
{

}

QJsonObject RequestSetTest::generateData()
{
    QJsonObject object;
    object["parameter"] = "test";
    object["requestType"] = "set";
    return object;
}
