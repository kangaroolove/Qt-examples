#include "Widget.h"
#include "KeyEventHandler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget widget;
    widget.installEventFilter(KeyEventHandler::getInstance());
    widget.show();

    return a.exec();
}
