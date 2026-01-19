#include "Widget.h"

#include <QComboBox>
#include <QDebug>
#include <QListView>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    auto box = new QComboBox(this);
    box->addItems({"AAAAAAAAAAAA", "BBBBBBBBBBBB"});

    auto listView = new QListView();
    listView->setStyleSheet(
        "QListView{font-size:30px;} QListView::item{height: 60px;}");
    box->setView(listView);
}