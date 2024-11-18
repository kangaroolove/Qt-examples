#include "Widget.h"
#include <QDebug>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{

    std::vector<int> vector = {
        1, 2, 3, 4, 5
    };

    for (auto& item : vector)
    {
        qDebug()<<item;
    }

    qDebug()<<"After";
    auto it = std::remove(vector.begin(), vector.end(), 3);
    vector.erase(it);
    qDebug()<<"distance = "<<std::distance(vector.begin(), it);

    for (auto& item : vector)
    {
        qDebug()<<item;
    }
}

Widget::~Widget()
{

}