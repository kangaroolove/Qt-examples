#pragma once

#include <QWidget>

class QTextEdit;
class QPushButton;
class Client;
class QLabel;

class ClientWidget : public QWidget
{
public:
    ClientWidget(QWidget* parent = nullptr);
    ~ClientWidget();

private:
    void initGui();
    void connectServer();
    void bindConnections();

    QLabel* m_displayLabel;
    Client* m_client;
};