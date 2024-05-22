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
    void screenRemoved(QScreen *screen);
protected:
    void showEvent(QShowEvent *event);
private:
    QByteArray m_geometry;
    QRect m_rect;
};