#include "ServerWorker.h"
#include "DaqcClientDef.h"
#include "ResourceManager.h"
#include <QBuffer>
#include <QDataStream>

ServerWorker::ServerWorker() :
    m_sharedMemory(new QSharedMemory("Cms/sharedMemory", this))
{
    connect(ResourceManager::getInstance(), &ResourceManager::frameReady, this, &ServerWorker::frameReady);
}

ServerWorker::~ServerWorker()
{

}

void ServerWorker::frameReady(const QImage &image)
{
    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);
    QDataStream stream(&buffer);
    stream << image;
    int size = buffer.size();

    if (!m_sharedMemory->create(size))
        return;

    m_sharedMemory->lock();
    char* to = (char*)m_sharedMemory->data();
    const char* from = buffer.data().data();
    memcpy(to, from, qMin(m_sharedMemory->size(), size));
    m_sharedMemory->unlock();
}

void ServerWorker::handleUpdateRequest(const QString &parameter, const QVariant &valueTypes, const QVariant &values)
{
    ResourceManager::getInstance()->handleUpdate(parameter, valueTypes, values);
}