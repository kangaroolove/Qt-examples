#include "HoverDialog.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>

HoverDialog::HoverDialog(QWidget* parent)
    : QDialog(parent),
      m_parent(parent),
      m_button(new QPushButton("Click")),
      m_contentWidget(new Content()) {
    initGui();
    bindConnections();
}

void HoverDialog::initGui() {
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_button->setFixedSize(90, 90);

    auto layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addStretch();
    layout->addWidget(m_button);
    layout->addStretch();

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_contentWidget);
    mainLayout->addLayout(layout);

    m_contentWidget->hide();
    resize(400, 90);
}

void HoverDialog::bindConnections() {
    connect(m_button, &QPushButton::clicked, this, [this] {
        static bool isBig = false;
        isBig ? m_contentWidget->hide() : m_contentWidget->show();
        isBig ? this->setFixedHeight(90) : this->setFixedHeight(180);
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

Content::Content(QWidget* parent) { initGui(); }

void Content::initGui() {
    auto label = new QLabel("Hi, I am the content!");

    auto button = new QPushButton("Cross");

    auto layout = new QHBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(button);

    setFixedHeight(90);
}
