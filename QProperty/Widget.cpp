#include "Widget.h"
#include "MyClass.h"
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent) {
  auto myClass = new MyClass(this);
  connect(myClass, &MyClass::visibleChanged, this,
          [this](bool visible) { qDebug() << "New visible = " << visible; });

  myClass->setProperty("visible", false);
  myClass->setProperty("visible", true);
  myClass->setProperty("visible", false);
}

Widget::~Widget() {}