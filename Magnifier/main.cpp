#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QObject>

#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Widget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Widget w;
    w.show();

    GraphicsScene scene;
    GraphicsView view(&scene);

    QObject::connect(&view, &GraphicsView::fitInViewScaleChanged, &scene,
                     &GraphicsScene::onFitInViewScaleChanged);

    view.show();

    return a.exec();
}
