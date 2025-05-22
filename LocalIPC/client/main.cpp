#include "ClientWidget.h"
#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    ClientWidget widget;
    widget.show();

    return app.exec();
}
