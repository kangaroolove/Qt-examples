#pragma once

#include <QDialog>

class QPushButton;

class HoverDialog : public QDialog
{
public:
    HoverDialog(QWidget* parent = nullptr);
private:
    void initGui();

    QPushButton* m_button;
};