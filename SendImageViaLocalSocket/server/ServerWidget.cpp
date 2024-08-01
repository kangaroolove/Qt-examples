#include "ServerWidget.h"
#include "Server.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>

ServerWidget::ServerWidget(QWidget* parent) : QWidget(parent)
    , m_server(new Server(this))
    , m_openFileButton(new QPushButton("Open file", this))
    , m_clearFileListButton(new QPushButton("Clear file list", this))
    , m_fileListTextEdit(new QTextEdit(this))
    , m_timerGapLabel(new QLabel("Timer interval:", this))
    , m_timerInput(new QLineEdit(this))
    , m_timerGapUnitLabel(new QLabel("ms", this))
    , m_autoSendButton(new QPushButton("Auto Send", this))
    , m_stopButton(new QPushButton("Stop", this))
    , m_timer(new QTimer(this))
    , m_currentFileIndex(0)
{
    initGui();
    bindConnections();
    startServer();
}

ServerWidget::~ServerWidget()
{

}

void ServerWidget::onAutoSendButtonClicked()
{
    auto text = m_fileListTextEdit->toPlainText();
    if (text.isEmpty())
    {
        QMessageBox::critical(this, "Critical", "You didn't choose any files!");
        return;
    }

    auto fileListText = m_fileListTextEdit->toPlainText();
    m_fileList = fileListText.split("\n");
    if (m_fileList.size() == 0)
        return;

    m_currentFileIndex = 0;

    // auto interval = m_timerInput->text().toInt();
    // m_timer->setInterval(interval);
    // m_timer->start();
}

void ServerWidget::onOpenFileButtonClicked()
{
    auto fileNames = QFileDialog::getOpenFileNames(this, "Open file", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), "Image(*.png)");
    if (fileNames.size() == 0)
    {
        QMessageBox::critical(this, "Error", "You didn't choose any files");
        return;
    }

    for (auto& fileName : fileNames)
        m_fileListTextEdit->append(fileName);
}

void ServerWidget::onClearFileListButtonClicked()
{
    m_fileListTextEdit->clear();
}

void ServerWidget::onStopButtonClicked()
{
    m_timer->stop();
}

void ServerWidget::onTimerTimeout()
{
    QString fileName = m_fileList.at(m_currentFileIndex);
    QImage image(fileName);
    m_server->sendImage(image);

    if (m_currentFileIndex < m_fileList.size())
        m_currentFileIndex++;
    else 
        m_currentFileIndex = 0;
}

void ServerWidget::initGui()
{
    auto layout = new QVBoxLayout(this);
    layout->addLayout(getFileButtonLayout());
    layout->addWidget(m_fileListTextEdit);
    layout->addLayout(getTimerLayout());
    layout->addWidget(m_autoSendButton);
    layout->addWidget(m_stopButton);

    m_fileListTextEdit->setReadOnly(true);
    m_timerInput->setText("16");
}

void ServerWidget::startServer()
{
    if (!m_server->start())
        qDebug()<<"Server listen error";
}

void ServerWidget::bindConnections()
{
    connect(m_autoSendButton, &QPushButton::clicked, this, &ServerWidget::onAutoSendButtonClicked);
    connect(m_openFileButton, &QPushButton::clicked, this, &ServerWidget::onOpenFileButtonClicked);
    connect(m_stopButton, &QPushButton::clicked, this, &ServerWidget::onStopButtonClicked);
    connect(m_clearFileListButton, &QPushButton::clicked, this, &ServerWidget::onClearFileListButtonClicked);
    connect(m_timer, &QTimer::timeout, this, &ServerWidget::onTimerTimeout);
}

QHBoxLayout *ServerWidget::getFileButtonLayout()
{
    auto layout = new QHBoxLayout();
    layout->addWidget(m_openFileButton);
    layout->addWidget(m_clearFileListButton);
    return layout;
}

QHBoxLayout *ServerWidget::getTimerLayout()
{
    auto layout = new QHBoxLayout();
    layout->addWidget(m_timerGapLabel);
    layout->addWidget(m_timerInput);
    layout->addWidget(m_timerGapUnitLabel);
    return layout;
}
