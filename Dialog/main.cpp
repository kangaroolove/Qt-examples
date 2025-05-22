#include "Dialog.h"
#include "Widget.h"
#include <QApplication>
#include <QDebug>
#include <QObject>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget widget;
    widget.show();

    Dialog dialog(&widget);
    QObject::connect(&dialog, &QDialog::finished, [](int result) {
        qDebug() << "Dialog result = " << result;
    });

    // The following solutions are different from calling exec() function.
    // show()/open() returns control to the caller immediately,

    // Solution 1 Qt::ApplicationModal
    // dialog.setModal(true);
    // dialog.show();

    // Solution 2
    // dialog.setWindowModality(Qt::ApplicationModal);
    // dialog.show();

    // Solution 3 Qt::windowModality
    dialog.open();

    return a.exec();
}
