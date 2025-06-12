#include "ServerWidget.h"
#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    ServerWidget widget;
    widget.show();

    return app.exec();
}
