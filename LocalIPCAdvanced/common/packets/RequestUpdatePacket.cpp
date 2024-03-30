#include "RequestUpdatePacket.h"
#include "DaqcClientDef.h"
#include <QJsonObject>
#include <QJsonArray>

RequestUpdatePacket::RequestUpdatePacket(const QString& parameter, const QVariant& values, const QVariant& valueTypes) :
    RequestPacket(parameter, values, valueTypes)
{
}

RequestUpdatePacket::RequestUpdatePacket(const RequestUpdatePacket &packet) :
    RequestPacket(getParameter(), getValues(), getValueTypes())
{
}

RequestUpdatePacket::~RequestUpdatePacket()
{

}

RequestUpdatePacket RequestUpdatePacket::fromJson(const QJsonObject &object)
{
    QString parameter = object["data"].toObject()["parameter"].toString();
    QVariant valueTypes = object["data"].toObject()["valueTypes"].toVariant();
    QVariant values = object["data"].toObject()["values"].toVariant();
    return RequestUpdatePacket(parameter, values, valueTypes);
}

QJsonObject RequestUpdatePacket::generateData()
{
    QJsonObject object;
    object["parameter"] = m_parameter;
    object["requestType"] = "update";
    object["valueTypes"] = QJsonArray::fromStringList(m_valueTypes.toStringList());
    object["values"] = QJsonArray::fromVariantList(m_values.toList());
    return object;
}
