#include "Widget.h"
#include <QBuffer>
#include <QByteArray>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

Widget::Widget(QWidget *parent) : QWidget(parent) {
  QImage image("D:/1.png");

  QJsonObject object;
  object["image"] = QImageToQJsonValue(image);
  QJsonDocument doc(object);
  doc.toJson(QJsonDocument::Compact);
  qDebug() << doc;

  QImage convertImage = QJsonValueToQImage(object["image"]);
  qDebug() << "convertImage.width() = " << convertImage.width();
  qDebug() << "convertImage.height() = " << convertImage.height();
}

Widget::~Widget() {}

QJsonValue Widget::QImageToQJsonValue(const QImage &image) {
  QByteArray imageData;
  QBuffer buffer(&imageData);
  image.save(&buffer, "PNG");

  return QJsonValue::fromVariant(buffer.data().toBase64());
}

QImage Widget::QJsonValueToQImage(const QJsonValue &value) {
  QImage image;
  image.loadFromData(QByteArray::fromBase64(value.toVariant().toByteArray()),
                     "PNG");
  return image;
}
