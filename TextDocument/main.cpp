#include "Widget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget widget;
    widget.showMaximized();

    return a.exec();
}
