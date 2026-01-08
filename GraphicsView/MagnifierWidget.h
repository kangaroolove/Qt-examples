#pragma once

#include <QLabel>

class MagnifierWidget : public QLabel {
    Q_OBJECT
public:
    MagnifierWidget(QWidget *parent = nullptr);
};