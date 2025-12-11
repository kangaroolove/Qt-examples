#include "HoverDialog.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QObject>
#include <QPushButton>

HoverDialog::HoverDialog(QWidget* parent)
    : QDialog(parent), m_parent(parent), m_button(new QPushButton("Click")) {
    initGui();
    bindConnections();
}

void HoverDialog::initGui() {
    setWindowFlag(Qt::FramelessWindowHint);
    // setAttribute(Qt::WA_TranslucentBackground);

    m_button->setFixedSize(90, 90);

    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addStretch();
    layout->addWidget(m_button);
    layout->addStretch();

    resize(400, 90);

    setObjectName("Dialog");
    // setStyleSheet("QDialog#Dialog{background-color:rgba(0, 255, 0,50%);}");
}

void HoverDialog::bindConnections() {
    connect(m_button, &QPushButton::clicked, this, [this] {
        static bool isBig = false;
        isBig ? this->setFixedHeight(90) : this->setFixedHeight(300);
        isBig = !isBig;

        this->move(
            m_parent->mapToGlobal(QPoint(0, m_parent->height() - height())));
    });
}

bool HoverDialog::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::Resize) {
        this->setFixedWidth(m_parent->width());
        this->move(
            m_parent->mapToGlobal(QPoint(0, m_parent->height() - height())));
        return false;
    }

    return QDialog::eventFilter(obj, event);
}
