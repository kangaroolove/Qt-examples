#include "Widget.h"
#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QPushButton>
#include <QTouchEvent>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_AcceptTouchEvents);
    auto layout = new QVBoxLayout(this);
    auto button = new QPushButton("Please click");
    connect(button, &QPushButton::clicked, this,
            [this] { qDebug() << "You clicked the button"; });

    layout->addWidget(button);
    resize(400, 300);
}

Widget::~Widget() {}

bool Widget::event(QEvent *event) {
    if (event->type() == QEvent::TouchBegin ||
        event->type() == QEvent::TouchUpdate ||
        event->type() == QEvent::TouchEnd) {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        const QList<QTouchEvent::TouchPoint> &touchPoints =
            touchEvent->touchPoints();
        qDebug() << "touch type = " << event->type();
        if (!touchPoints.isEmpty()) {
            qDebug() << "touchPoints are not empty";
            const QTouchEvent::TouchPoint &touchPoint = touchPoints.first();
            QPoint pos = touchPoint.pos().toPoint();

            // Create a mouse event
            QMouseEvent mouseEvent(QEvent::MouseButtonPress, pos,
                                   Qt::LeftButton, Qt::LeftButton,
                                   Qt::NoModifier);

            // Process the mouse event
            QApplication::sendEvent(this, &mouseEvent);

            // You can also handle MouseButtonRelease if needed
            QMouseEvent mouseReleaseEvent(QEvent::MouseButtonRelease, pos,
                                          Qt::LeftButton, Qt::LeftButton,
                                          Qt::NoModifier);
            QApplication::sendEvent(this, &mouseReleaseEvent);
        }
        return true;
    }
return QWidget::event(event);
}
