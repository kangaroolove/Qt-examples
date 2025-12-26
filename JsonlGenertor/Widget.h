#pragma once

#include <QWidget>

class QPushButton;
class QTextEdit;

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

private:
    void initGui();

    QPushButton* m_generateButton;
    QTextEdit* m_textEdit;
};