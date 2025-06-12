#include "Widget.h"
#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 200, 200);
    scene.addText("Hello, world");

    auto text2 = scene.addText("Second Text");
    text2->setPos(50, 50);

    QGraphicsView view(&scene);
    view.show();

    qDebug() << scene.sceneRect();

    return a.exec();
}
