#pragma once

#include <QWidget>
#include <memory>

class QTextEdit;
class QPushButton;
class QLabel;
class Server;
class QLineEdit;
class QHBoxLayout;

class ServerWidget : public QWidget
{
public:
    ServerWidget(QWidget* parent = nullptr);
    ~ServerWidget();
private slots:
    void onAutoSendButtonClicked();
    void onSendButtonClicked();
private:
    void initGui();
    void startServer();
    void bindConnections();
    QHBoxLayout* getFileButtonLayout();
    QHBoxLayout* getTimerLayout();

    std::unique_ptr<QTimer> m_timer;
    QTextEdit* m_fileListTextEdit;
    QPushButton* m_openButton;
    QPushButton* m_clearButton;
    QLabel* m_timerGapLabel;
    QLineEdit* m_timerInput;
    QLabel* m_timerGapUnitLabel;
    QPushButton* m_sendButton;

    Server* m_server;
};