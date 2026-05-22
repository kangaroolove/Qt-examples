#include "Widget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    m_statusLabel = new QLabel("Idle", this);
    m_startBtn = new QPushButton("Start", this);
    m_stopBtn = new QPushButton("Stop", this);
    m_stopBtn->setEnabled(false);

    auto *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_startBtn);
    btnLayout->addWidget(m_stopBtn);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_statusLabel);
    layout->addLayout(btnLayout);

    connect(m_startBtn, &QPushButton::clicked, this, &Widget::onStart);
    connect(m_stopBtn, &QPushButton::clicked, this, &Widget::onStop);

    setWindowTitle("CPU Stress Test");
    resize(300, 100);
}

Widget::~Widget() {
    onStop();
}

void Widget::onStart() {
    if (m_running) return;
    m_running = true;

    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 4;

    for (unsigned int i = 0; i < numThreads; ++i) {
        m_workers.emplace_back([this]() {
            volatile double x = 1.0;
            while (m_running) {
                x = x * 1.0000001 + 0.0000001;
            }
        });
    }

    m_startBtn->setEnabled(false);
    m_stopBtn->setEnabled(true);
    m_statusLabel->setText(QString("Running on %1 threads...").arg(numThreads));
}

void Widget::onStop() {
    if (!m_running) return;
    m_running = false;
    for (auto &t : m_workers)
        if (t.joinable()) t.join();
    m_workers.clear();

    m_startBtn->setEnabled(true);
    m_stopBtn->setEnabled(false);
    m_statusLabel->setText("Idle");
}
