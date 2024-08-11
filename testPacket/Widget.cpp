#include "Widget.h"
#include "RequestUpdatePacket.h"
#include <QDebug>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    QVariantList values = { 10 };
    QStringList valueTypes = { "int", "double", "string"};
    RequestUpdatePacket packet("gain", values, valueTypes);
    qDebug()<<"packet1";
    packet.printfSelf();

    auto data = packet.toJson();
    qDebug()<<"data = "<<data;

    qDebug()<<"packet2";
    RequestUpdatePacket packet2 = RequestUpdatePacket::fromJson(data);
    packet2.printfSelf();
}

Widget::~Widget()
{

}