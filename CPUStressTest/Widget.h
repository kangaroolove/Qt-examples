#pragma once

#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <atomic>
#include <thread>
#include <vector>

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onStart();
    void onStop();

private:
    QPushButton *m_startBtn;
    QPushButton *m_stopBtn;
    QLabel *m_statusLabel;
    std::atomic<bool> m_running{false};
    std::vector<std::thread> m_workers;
};
