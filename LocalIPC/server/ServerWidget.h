#pragma once

#include <QWidget>

class QTextEdit;
class QPushButton;
class QLabel;
class Server;

class ServerWidget : public QWidget
{
public:
    ServerWidget(QWidget* parent = nullptr);
    ~ServerWidget();

private:
    void initGui();
    void startServer();
    void bindConnections();

    QTextEdit* m_receiveTextEdit;
    QTextEdit* m_sendTextEdit;
    QPushButton* m_sendButton;
    QLabel* m_statusLabel;
    Server* m_server;
};