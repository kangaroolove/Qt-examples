#include "Widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents);

    QApplication a(argc, argv);
    Widget widget;
    widget.show();

    return a.exec();
}
