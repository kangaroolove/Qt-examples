#pragma once

#include <QByteArray>
#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow();
  ~MainWindow();
private slots:
  void screenAdded(QScreen *screen);

protected:
  void showEvent(QShowEvent *event);

private:
  void printGeometry();

  QRect m_rect;
};