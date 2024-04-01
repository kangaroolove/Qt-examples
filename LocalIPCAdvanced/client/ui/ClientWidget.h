#pragma once

#include <QWidget>

class QTextEdit;
class QPushButton;
class DaqcClient;
class QLabel;

class ClientWidget : public QWidget
{
public:
    ClientWidget(QWidget* parent = nullptr);
    ~ClientWidget();
private slots:
    void onInitButtonClicked();

private:
    void initGui();
    void bindConnections();

    QTextEdit* m_receiveTextEdit;
    QTextEdit* m_sendTextEdit;
    QPushButton* m_sendButton;
    QPushButton* m_initButton;
    DaqcClient* m_client;
    QLabel* m_imageLabel;
};