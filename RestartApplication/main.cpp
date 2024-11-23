#include "Widget.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget widget;
  widget.show();

  return a.exec();
}
