#pragma once

#include <QObject>

class MyClass : public QObject {
  Q_OBJECT
  Q_PROPERTY(
      bool visible READ getVisible WRITE setVisible NOTIFY visibleChanged)
public:
  MyClass(QObject *parent = nullptr);
  ~MyClass();

  void setVisible(bool visible);
  bool getVisible() const;
signals:
  void visibleChanged(bool visible);

private:
  bool m_visible;
};