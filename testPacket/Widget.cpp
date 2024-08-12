#include "Widget.h"
#include "RequestUpdatePacket.h"
#include "FramePacket.h"
#include "ParameterInfoPacket.h"
#include <QDebug>
#include <QFile>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    testRequestUpdatePacket();
    testFramePacket();
    testParameterPacket();
}

Widget::~Widget()
{

}

void Widget::testRequestUpdatePacket()
{
    qDebug()<<"\ntestRequestUpdatePacket";
    QVariantList values = { 10 };
    QStringList valueTypes = { "int", "double", "string"};
    RequestUpdatePacket packet("gain", values, valueTypes);
    qDebug()<<"packet1";
    packet.printfSelf();

    auto sendData = packet.toBinary();
    qDebug()<<"sendData = "<<sendData;

    QByteArray data;
    QDataStream stream(sendData);
    stream >> data; 

    qDebug()<<"data = "<<data;

    qDebug()<<"packet2";
    RequestUpdatePacket packet2 = RequestUpdatePacket::fromJson(data);
    packet2.printfSelf();
}

void Widget::testFramePacket()
{
    qDebug()<<"\ntestFramePacket";

    FramePacket packet(QImage(), ImageChannel::DEFAULT_OR_DUAL_LINEAR);
    qDebug()<<"packet1";
    packet.printfSelf();

    auto sendData = packet.toBinary();
    qDebug()<<"sendData = "<<sendData;

    QByteArray data;
    QDataStream stream(sendData);
    stream >> data; 

    qDebug()<<"data = "<<data;

    qDebug()<<"packet2";
    FramePacket packet2 = FramePacket::fromJson(data);
    packet2.printfSelf();
}

void Widget::testParameterPacket()
{
    qDebug()<<"\ntestParameterPacket";


}
