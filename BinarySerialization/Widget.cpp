#include "Widget.h"
#include <QFile>
#include <QDataStream>
#include <QJsonDocument>
#include <QBuffer>
#include <QJsonValue>
#include <QVariant>
#include <QJsonObject>
#include <QDebug>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    QImage image("D:/2.png");
    // the size is the smallest
    saveImageToBinary(image);
    // the size is less than saveImageToJsonBinary
    saveImageToJson(image);
    // the size is the biggest
    saveImageToJsonBinary(image);
}

Widget::~Widget()
{

}

void Widget::saveImageToBinary(const QImage &image)
{
    QFile file("D:/saveImageToBinary.txt");
    if (!file.open(QIODevice::WriteOnly))
        return;

    QDataStream stream(&file);
    stream << image;
    file.close();
}

void Widget::saveImageToJsonBinary(const QImage &image)
{
    QFile file("D:/saveImageToJsonBinary.txt");
    if (!file.open(QIODevice::WriteOnly))
        return;
    
    QByteArray data;
    QBuffer buffer(&data);
    image.save(&buffer, "PNG");

    QJsonObject object;
    object["image"] = QJsonValue::fromVariant(buffer.data().toBase64());
    QJsonDocument doc(object);

    file.write(doc.toBinaryData());
    file.close();
}

void Widget::saveImageToJson(const QImage &image)
{
    QFile file("D:/saveImageToJson.txt");
    if (!file.open(QIODevice::WriteOnly))
        return;
    
    QByteArray data;
    QBuffer buffer(&data);
    image.save(&buffer, "PNG");

    QJsonObject object;
    object["image"] = QJsonValue::fromVariant(buffer.data().toBase64());
    QJsonDocument doc(object);

    file.write(doc.toJson(QJsonDocument::Compact));
    file.close();
}
