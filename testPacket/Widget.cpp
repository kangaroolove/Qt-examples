#include "Widget.h"
#include "RequestUpdatePacket.h"
#include <QDebug>
#include <QFile>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    QVariantList values = { 10 };
    QStringList valueTypes = { "int", "double", "string"};
    RequestUpdatePacket packet("gain", values, valueTypes);
    qDebug()<<"packet1";
    packet.printfSelf();

    auto data = packet.toBinary();
    qDebug()<<"data = "<<data;

    QImage image("D:/2.png");

    QFile file("D:/3.dat");

    qDebug()<<"type = "<<(int)Packet::getTypeFromJson(data);

    qDebug()<<"packet2";
    RequestUpdatePacket packet2 = RequestUpdatePacket::fromJson(data);
    packet2.printfSelf();
}

Widget::~Widget()
{

}