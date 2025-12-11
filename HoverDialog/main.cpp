#include "Widget.h"
#include "HoverDialog.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget widget;
    HoverDialog dialog(&widget);
    widget.installEventFilter(&dialog);
    dialog.show();
    widget.show();

    return a.exec();
}
