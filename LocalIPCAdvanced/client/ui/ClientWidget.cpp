#include "ClientWidget.h"
#include "DaqcClient.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QHBoxLayout>

ClientWidget::ClientWidget(QWidget* parent) : 
    QWidget(parent),
    m_sendButton(new QPushButton("Send", this)),
    m_client(new DaqcClient(this)),
    m_imageLabel(new QLabel(this)),
    m_initButton(new QPushButton("Init", this)),
    m_acuiButton(new QPushButton(("ACUI"), this)),
    m_acuiLabel(new QLabel("1", this)),
    m_dualModeButton(new QPushButton("Dual Mode", this))
{
    initGui();
    bindConnections();
    m_client->connectToServer();
}

ClientWidget::~ClientWidget()
{

}

void ClientWidget::onAcuiButtonClicked()
{
}

void ClientWidget::onDualModeButtonClicked(bool clicked)
{
    m_client->setDualMode(clicked);
}

void ClientWidget::onInitButtonClicked()
{
    std::vector<int> probeList = { 11, 12, 15, 8};
    int currentPort = 0;
    int currentExamId = 10;

    m_client->legacyInit(0);
    for (int i = 0; i < probeList.size(); ++i)
        m_client->legacyFProbeType(i, probeList.at(i));
    m_client->legacySetImageProcess(1);
    m_client->legacySetProbePOS(currentPort);
    m_client->legacySetPwifBuffms(0);
    m_client->legacySetScanMode(0);
    m_client->legacySetExamTypeID(currentExamId);
    m_client->legacyStart();
}

void ClientWidget::initGui()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QHBoxLayout *acuiLayout = new QHBoxLayout;
    acuiLayout->addWidget(m_acuiLabel);
    acuiLayout->addWidget(m_acuiButton);

    layout->addWidget(m_sendButton);
    layout->addWidget(m_initButton);
    layout->addWidget(m_dualModeButton);
    layout->addLayout(acuiLayout);
    layout->addWidget(m_imageLabel);

    m_dualModeButton->setCheckable(true);

    this->resize(800, 600);
}

void ClientWidget::bindConnections()
{
    connect(m_sendButton, &QPushButton::clicked, this, [this]{
        //m_client->testSetApi(true);
        qDebug()<<"m_client->testGetApi() = "<<m_client->testGetApi();
    });

    connect(m_client, &DaqcClient::imageReceived, this, [this](QImage image){
        qDebug()<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
        auto channel = m_client->getImageCurrentChannel();
        qDebug()<<"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
        if (channel == 0)
            m_imageLabel->setPixmap(QPixmap::fromImage(image));
        else if (channel == 1)
            m_imageLabel2->setPixmap(QPixmap::fromImage(image));
    });

    connect(m_client, &DaqcClient::connected, this, []{
        qDebug()<<"trigger connect";
    });

    connect(m_initButton, &QPushButton::clicked, this, &ClientWidget::onInitButtonClicked);
    connect(m_acuiButton, &QPushButton::clicked, this, &ClientWidget::onAcuiButtonClicked);
    connect(m_dualModeButton, &QPushButton::clicked, this, &ClientWidget::onDualModeButtonClicked);
}
