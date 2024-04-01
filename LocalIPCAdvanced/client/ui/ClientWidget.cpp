#include "ClientWidget.h"
#include "DaqcClient.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>



ClientWidget::ClientWidget(QWidget* parent) : 
    QWidget(parent),
    m_receiveTextEdit(new QTextEdit(this)),
    m_sendTextEdit(new QTextEdit(this)),
    m_sendButton(new QPushButton("Send", this)),
    m_client(new DaqcClient(this)),
    m_imageLabel(new QLabel(this)),
    m_initButton(new QPushButton("Init", this))
{
    initGui();
    bindConnections();
    m_client->connectToServer();
}

ClientWidget::~ClientWidget()
{

}

void ClientWidget::onInitButtonClicked()
{
    std::vector<int> probeList = {};
    int currentPort = 0;
    int currentExamId = 10;

    m_client->legacyInit(0);

    for (int i = 0; i < probeList.size(); ++i)
        m_client->legacyFProbeType(i, probeList.at(i));
    m_client->legacySetImageProcess(1);
    m_client->legacySetProbePOS(currentPort);
    m_client->legacySetExamTypeID(currentExamId);
    m_client->legacySetPwifBuffms(0);
    m_client->legacySetScanMode(0);
    m_client->legacyStart();
}

void ClientWidget::initGui()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel* receiveLabel = new QLabel("Receive:", this);
    QLabel* sendLabel = new QLabel("Send:", this);

    layout->addWidget(receiveLabel);
    layout->addWidget(m_receiveTextEdit);
    layout->addWidget(sendLabel);
    layout->addWidget(m_sendTextEdit);
    layout->addWidget(m_sendButton);
    layout->addWidget(m_initButton);
    layout->addWidget(m_imageLabel);
}

void ClientWidget::bindConnections()
{
    connect(m_sendButton, &QPushButton::clicked, this, [this]{
        //m_client->sendMessage(m_sendTextEdit->toPlainText());
        //m_sendTextEdit->clear();

        //m_client->testSetApi(true);
        qDebug()<<"m_client->testGetApi() = "<<m_client->testGetApi();
    });
    connect(m_client, &DaqcClient::messageReceived, this, [this](const QString& msg){
        m_receiveTextEdit->append(msg);
    });

    connect(m_client, &DaqcClient::imageReceived, this, [this](QImage image){
        m_imageLabel->setPixmap(QPixmap::fromImage(image));
    });

    connect(m_client, &DaqcClient::connected, this, []{
        qDebug()<<"trigger connect";
    });

    connect(m_initButton, &QPushButton::clicked, this, &ClientWidget::onInitButtonClicked);
}
