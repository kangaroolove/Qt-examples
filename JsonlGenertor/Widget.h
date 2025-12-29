#pragma once

#include <QWidget>

class QPushButton;
class QTextEdit;
class QLineEdit;

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

private slots:
    void onGenerateButtonClicked();
    void onDirChooseButtonClicked();

private:
    void initGui();
    void bindConnections();

    QLineEdit* m_dirLineEdit;
    QPushButton* m_dirChooseButton;
    QPushButton* m_generateButton;
    QTextEdit* m_textEdit;
};