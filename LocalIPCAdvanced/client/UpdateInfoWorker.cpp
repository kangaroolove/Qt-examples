#include "UpdateInfoWorker.h"
#include "DaqcClient.h"
#include <QTimer>

UpdateInfoWorker::UpdateInfoWorker(DaqcClient* client, QObject* parent) :
    QObject(parent),
    m_client(client),
    m_timer(new QTimer(this))
{
    m_timer->setInterval(400);
    connect(m_timer, &QTimer::timeout, this, &UpdateInfoWorker::updateInfoFromServer);
}

UpdateInfoWorker::~UpdateInfoWorker()
{

}

void UpdateInfoWorker::startUpdate()
{
    m_timer->start();
}

void UpdateInfoWorker::updateInfoFromServer()
{
    m_client->requestSpacingX();
    m_client->requestSpacingY();
    m_client->requestLegacyGetParameter(6);
    m_client->requestLegacyGetParameter(7);
    m_client->requestLegacyGetParameter(8);
    m_client->requestLegacyGetParameter(50);
    m_client->requestIsDualModeOn();
    m_client->requestBGain();
}