#pragma once

#include <QLocalSocket>

class ClientWorker;
class ClientWorker;
class QThread;

class Client : public QObject {
  Q_OBJECT
public:
  Client(QObject *parent = nullptr);
  ~Client();
  void sendMessage(const QString &msg);
  void connectToServer(const QString &name);
signals:
  void receiveMessage(const QString &msg);
  void sendMessageToWorker(const QString &msg);
  void connectServer(const QString &name);

private:
  ClientWorker *m_clientWorker;
  QThread *m_thread;
};