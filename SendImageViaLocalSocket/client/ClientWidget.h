#pragma once

#include <QWidget>

class QTextEdit;
class QPushButton;
class Client;
class QLabel;
class QThread;

class ClientWidget : public QWidget
{
    Q_OBJECT
public:
    ClientWidget(QWidget* parent = nullptr);
    ~ClientWidget();
signals:
    void connectToServer();
private:
    void initGui();
    void connectServer();
    void bindConnections();
    void initWorker();

    QLabel* m_displayLabel;
    Client* m_client;
    QThread* m_clientThread;
};