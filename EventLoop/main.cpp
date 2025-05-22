#include "Widget.h"
#include <QApplication>
#include <QDebug>
#include <QEventLoop>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget widget;
    widget.show();

    QEventLoop loop;
    QObject::connect(&widget, &Widget::quitEventLoop, &loop, &QEventLoop::quit);
    qDebug() << "You have started the event loop";
    loop.exec();
    qDebug() << "You have quitted the event loop";

    return a.exec();
}
