#include "Widget.h"
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QPushButton>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout(this);
  QPushButton *button = new QPushButton("External call", this);
  connect(button, &QPushButton::clicked, this, [this] {
    QString filePath =
        QCoreApplication::applicationDirPath() + "/testApplication.exe";
    QProcess *process = new QProcess(this);
    process->start(filePath);
    if (process->waitForStarted())
      qDebug() << "Starting testApplication is successful";
    else
      qDebug() << "Starting testApplication is failed";
  });
  layout->addWidget(button);
  this->resize(400, 300);
}

Widget::~Widget() {}