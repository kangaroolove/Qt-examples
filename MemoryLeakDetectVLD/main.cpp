#include "Widget.h"
#include <QApplication>
#include <vld.h>

// Before you run this application, make sure you have installed VLD.
// Because it will read the vld.ini file

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget widget;
  widget.show();

  return a.exec();
}
