#include "Widget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>

Widget::Widget(QWidget *parent) : QWidget(parent),
    m_generateButton(new QPushButton("Generate", this)),
    m_textEdit(new QTextEdit(this)) {
    initGui();
}

void Widget::initGui() {
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_textEdit);
    layout->addWidget(m_generateButton);
    resize(800, 600);
}
