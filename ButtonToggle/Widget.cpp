#include "Widget.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>

Widget::Widget(QWidget *parent) : QWidget(parent) {
  auto layout = new QHBoxLayout(this);
  auto btn1 = new QPushButton("First");
  btn1->setCheckable(true);
  connect(btn1, &QPushButton::toggled, this,
          [this](bool checked) { qDebug() << "btn1 checked = " << checked; });

  auto btn2 = new QPushButton("Test");
  connect(btn2, &QPushButton::clicked, this,
          [this, btn1] { btn1->setChecked(true); });

  layout->addWidget(btn1);
  layout->addWidget(btn2);
}