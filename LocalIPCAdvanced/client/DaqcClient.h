#pragma once

#include "Client.h"

class DaqcClient : public Client
{
    Q_OBJECT
public:
    DaqcClient(QObject* parent);
    ~DaqcClient();
    void testGetApi();
    void testSetApi(bool isTest);
private:

};