#include "MainWindow.h"
#include "SecondWindow.h"
#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QScreen>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto screens = a.screens();
    MainWindow mainWindow;
    SecondWindow secondWindow;

    if (screens.size() == 2) {
        mainWindow.setGeometry(screens[0]->geometry());
        mainWindow.showFullScreen();

        secondWindow.setGeometry(screens[1]->geometry());
        secondWindow.showFullScreen();
} else if (screens.size() == 1) {
    mainWindow.setGeometry(screens.first()->geometry());
    secondWindow.setGeometry(screens.first()->geometry());
    mainWindow.show();
    secondWindow.show();
}

return a.exec();
}
