#pragma once

#include <QWidget>

class FlowLayout;

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);

private:
    FlowLayout* m_flowLayout;
};