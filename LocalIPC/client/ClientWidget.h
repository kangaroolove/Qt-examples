#pragma once

#include <QWidget>

class QTextEdit;
class QPushButton;
class Client;

class ClientWidget : public QWidget
{
public:
    ClientWidget(QWidget* parent = nullptr);
    ~ClientWidget();

private:
    void initGui();
    void connectServer();
    void bindConnections();

    QTextEdit* m_receiveTextEdit;
    QTextEdit* m_sendTextEdit;
    QPushButton* m_sendButton;
    Client* m_client;
};