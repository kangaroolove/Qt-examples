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
    void onOpenFileButtonClicked();
    void onClearFileListButtonClicked();
    void onStopButtonClicked();
    void onTimerTimeout();
private:
    void initGui();
    void startServer();
    void bindConnections();
    QHBoxLayout* getFileButtonLayout();
    QHBoxLayout* getTimerLayout();

    QTextEdit* m_fileListTextEdit;
    QPushButton* m_openFileButton;
    QPushButton* m_clearFileListButton;
    QLabel* m_timerGapLabel;
    QLineEdit* m_timerInput;
    QLabel* m_timerGapUnitLabel;
    QPushButton* m_autoSendButton;
    QPushButton* m_stopButton;
    QTimer* m_timer;
    Server* m_server;
    QStringList m_fileList;
    int m_currentFileIndex;
};