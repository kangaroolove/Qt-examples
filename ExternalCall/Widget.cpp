#include "Widget.h"
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QPushButton>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent), m_process(nullptr) {
  QVBoxLayout *layout = new QVBoxLayout(this);
  QPushButton *button = new QPushButton("External call", this);

  connect(button, &QPushButton::clicked, this, [this] {
    QString filePath =
        QCoreApplication::applicationDirPath() + "/testApplication.exe";

    clearProcess();
    m_process = new QProcess(this);
    m_process->start(filePath);
    if (m_process->waitForStarted())
      qDebug() << "Starting testApplication is successful";
    else
      qDebug() << "Starting testApplication is failed";
  });
  layout->addWidget(button);
  this->resize(400, 300);
}

Widget::~Widget() { clearProcess(); }

void Widget::clearProcess() {
  if (m_process) {
    m_process->kill();
    m_process->waitForFinished();
  }
}