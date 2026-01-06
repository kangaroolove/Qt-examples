#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include "GraphicsView.h"
#include "Widget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QGraphicsScene scene;

    QPixmap pixmap("D:/1.jpg");
    scene.addPixmap(pixmap);

    scene.addText("Hello, world");

    auto text2 = scene.addText("Second Text");
    text2->setPos(50, 50);

    GraphicsView view(&scene);
    view.show();

    return a.exec();
}
