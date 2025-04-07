#include "Widget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QSlider>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    auto slider = new QSlider(Qt::Horizontal);
    // Define min-height is necessary otherwise you won't see a whole circle
    // margin = (grooveHeight - handleWidth) / 2
    slider->setStyleSheet("QSlider:horizontal {min-height: 36px; } \
        QSlider::groove:horizontal{height:10px;background:#2F3643;border-radius:5px;} \
        QSlider::handle:horizontal{background:#4E9D00; width:36px; border-radius:18px; margin:-13px 0;}");

    auto layout = new QVBoxLayout(this);
    layout->addWidget(slider);
}