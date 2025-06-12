#pragma once

#include <QWidget>
#include <memory>

class QProcess;

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QProcess *m_process;

    void clearProcess();
};