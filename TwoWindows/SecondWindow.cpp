#include "SecondWindow.h"
#include <QDebug>
#include <QGuiApplication>
#include <QLabel>
#include <QScreen>

SecondWindow::SecondWindow() {
  auto label = new QLabel("Second window", this);
  connect(qApp, &QGuiApplication::screenAdded, this,
          &SecondWindow::screenAdded);

  this->setObjectName("SecondWindow");
  this->setStyleSheet("QMainWindow#SecondWindow{background-color:blue;}");
}

SecondWindow::~SecondWindow() {}

void SecondWindow::showEvent(QShowEvent *event) {
  qDebug() << "save second geometry";
  m_geometry = saveGeometry();
  m_rect = geometry();
  qDebug() << "second rect = " << m_rect;
}

void SecondWindow::screenAdded(QScreen *screen) {
  auto screens = QGuiApplication::screens();
  if (screens.size() == 2) {
    qDebug() << "Restore second geometry";
    setGeometry(m_rect);
  }
}
