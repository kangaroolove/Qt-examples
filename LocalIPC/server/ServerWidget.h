#pragma once

#include <QWidget>
#include <memory>

class QTextEdit;
class QPushButton;
class QLabel;
class Server;
class QLineEdit;
class QHBoxLayout;

class ServerWidget : public QWidget {
public:
  ServerWidget(QWidget *parent = nullptr);
  ~ServerWidget();
private slots:
  void onAutoSendButtonClicked();
  void onSendButtonClicked();

private:
  void initGui();
  void startServer();
  void bindConnections();
  QHBoxLayout *getTimerLayout();
  std::unique_ptr<QTimer> m_timer;

  QTextEdit *m_receiveTextEdit;
  QTextEdit *m_sendTextEdit;
  QPushButton *m_sendButton;
  QPushButton *m_autoSendButton;
  QPushButton *m_stopSendButton;
  QLabel *m_statusLabel;
  Server *m_server;
  QLineEdit *m_timerIntervalInput;
};