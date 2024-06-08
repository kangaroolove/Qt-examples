#pragma once

#include <QDialog>

class Dialog : public QDialog
{
public:
    Dialog(QWidget* parent = nullptr);
    ~Dialog();
};