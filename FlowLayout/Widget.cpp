#include "Widget.h"
#include "flowlayout.h"
#include <QPushButton>
#include <QDebug>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    auto mainLayout = new QVBoxLayout(this);
    m_flowLayout = new FlowLayout(0, 10, 10);
    // m_flowLayout->addWidget(new QPushButton("Short"));

    auto addBtn = new QPushButton("Add", this);
    // addBtn->setFixedSize(200, 200);

    mainLayout->addLayout(m_flowLayout);
    mainLayout->addWidget(addBtn);

    connect(addBtn, &QPushButton::clicked, this, [this] {
        auto btn = new QPushButton("AAAAAAAAAAA");
        btn->setMinimumSize(100, 100);
        m_flowLayout->addWidget(btn);
        // this->adjustSize();
        // m_flowLayout->heightForWidth(600);
        // m_flowLayout->setGeometry(QRect(0, 0, 100, 200));
        m_flowLayout->update();
        this->adjustSize();
    });

    // auto shortButton = new QPushButton(tr("Short"));
    // flowLayout->addWidget();
    // flowLayout->addWidget(new QPushButton(tr("Short")));
    // flowLayout->addWidget(new QPushButton(tr("Short")));
    // flowLayout->addWidget(new QPushButton(tr("Short")));
    // flowLayout->addWidget(new QPushButton(tr("Short")));

    setWindowTitle(tr("Flow Layout"));
}