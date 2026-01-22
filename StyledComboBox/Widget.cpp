#include "Widget.h"

#include <QComboBox>
#include <QDateEdit>
#include <QDebug>
#include <QListView>
#include <QScroller>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    auto box = new QComboBox(this);
    box->setMaxVisibleItems(6);
    box->setObjectName("Box");
    // In order to increase the width of drop-down, padding-left is necessary
    box->setStyleSheet(
        "QComboBox#Box{ font-size:20px; padding-left:2px; height:58px;} "
        "QComboBox::drop-down{width: 48px; }");

    for (int i = 0; i < 30; ++i)
        box->addItem(QString::number(i));

    // custom drop-down list view
    auto listView = new QListView();
    listView->setStyleSheet(
        "QListView{font-size:20px;} QListView::item{height: "
        "60px;} "
        "QScrollBar:vertical { "
        "width : 48px; }");
    box->setView(listView);

    // Support gesture
    auto viewport = listView->viewport();
    listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QScroller::grabGesture(viewport, QScroller::LeftMouseButtonGesture);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(box);

    resize(800, 600);
}