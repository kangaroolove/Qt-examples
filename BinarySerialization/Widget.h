#pragma once

#include <QWidget>

class QImage;

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void saveImageToBinary(const QImage &image);
    void saveImageToJsonBinary(const QImage &image);
    void saveImageToJson(const QImage &image);
};