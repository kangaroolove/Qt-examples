#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include "GraphicsScene.h"
#include "GraphicsView.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    GraphicsScene scene;
    GraphicsView view(&scene);
    view.show();

    return a.exec();
}
