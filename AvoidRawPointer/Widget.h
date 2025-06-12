#pragma once

class A;

#include <QWidget>

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    void printf(A &a);
};