#pragma once

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
    QJsonValue QImageToQJsonValue(const QImage& image); 
    QImage QJsonValueToQImage(const QJsonValue& value);
};