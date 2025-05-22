#pragma once

#include <QByteArray>
#include <QMainWindow>

class SecondWindow : public QMainWindow {
    Q_OBJECT
public:
    SecondWindow();
    ~SecondWindow();
private slots:
    void screenAdded(QScreen *screen);

protected:
    void showEvent(QShowEvent *event);

private:
    QByteArray m_geometry;
    QRect m_rect;
};