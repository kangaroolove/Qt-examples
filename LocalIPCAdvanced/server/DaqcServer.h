#pragma once

#include "Server.h"
#include "daqclib.h"

using Daqc = DAQCLib::DAQC;
class DaqcServer : public Server
{
    Q_OBJECT
public:
    DaqcServer(QObject* parent = nullptr);
    ~DaqcServer();
    void start() override;
protected:
    HandleReceiveMessageTask* generateHandleRequestTask(const QByteArray& data) override;
private:
    Daqc* m_daqc;
};