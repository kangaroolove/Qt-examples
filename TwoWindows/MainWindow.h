#pragma once

#include <QMainWindow>
#include <QByteArray>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
private slots:
    void screenAdded(QScreen *screen);
protected:
    void showEvent(QShowEvent *event);
private:
    QRect m_rect;
};