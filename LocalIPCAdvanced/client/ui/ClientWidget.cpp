#include "ClientWidget.h"
#include "DaqcClient.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QButtonGroup>

ClientWidget::ClientWidget(QWidget* parent) : 
    QWidget(parent),
    m_testButton(new QPushButton("Send", this)),
    m_client(new DaqcClient(this)),
    m_imageLabel(new QLabel(this)),
    m_initButton(new QPushButton("Init", this)),
    m_imageLabel2(new QLabel(this)),
    m_dualModeButton(new QPushButton("Dual Mode", this)),
    m_probeList{11, 12, 15, 8},
    m_currentPort(0)
{
    m_examTypeMap = {
        {11, 10}
    };
    initGui();
    bindConnections();
    m_client->connectToServer();
}

ClientWidget::~ClientWidget()
{

}

void ClientWidget::onDualModeButtonClicked(bool clicked)
{
    m_client->setDualMode(clicked);
}

void ClientWidget::onInitButtonClicked()
{
    m_client->legacyInit(0);
    switchProbe(m_currentPort);
}

void ClientWidget::initGui()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_testButton);
    layout->addWidget(m_initButton);
    layout->addWidget(m_dualModeButton);
    layout->addWidget(getSwitchProbeGroupBox());
    layout->addWidget(m_imageLabel);
    layout->addWidget(m_imageLabel2);

    m_dualModeButton->setCheckable(true);

    this->resize(800, 600);
}

void ClientWidget::bindConnections()
{
    connect(m_testButton, &QPushButton::clicked, this, [this]{
        //m_client->testSetApi(true);
        qDebug()<<"m_client->testGetApi() = "<<m_client->testGetApi();
    });

    connect(m_client, &DaqcClient::imageReceived, this, [this](QImage image){
        auto channel = m_client->getImageCurrentChannel();
        if (channel == 0)
            m_imageLabel->setPixmap(QPixmap::fromImage(image));
        else if (channel == 1)
            m_imageLabel2->setPixmap(QPixmap::fromImage(image));
    });

    connect(m_initButton, &QPushButton::clicked, this, &ClientWidget::onInitButtonClicked);
    connect(m_dualModeButton, &QPushButton::clicked, this, &ClientWidget::onDualModeButtonClicked);
}

int ClientWidget::getExamTypeId(const int &probeId)
{
    auto it = m_examTypeMap.find(probeId);
    if (it != m_examTypeMap.end())
        return it->second;

    return -1;
}

QGroupBox *ClientWidget::getSwitchProbeGroupBox()
{
    QGroupBox* groupBox = new QGroupBox("Switch Probe", this);
    QHBoxLayout* layout = new QHBoxLayout(groupBox);
    QButtonGroup* buttonGroup = new QButtonGroup(this);
    for (size_t i = 0; i < m_probeList.size(); ++i)
    {
        QPushButton* button = new QPushButton(QString::number(m_probeList[i]), this);
        button->setProperty("port", i);
        button->setCheckable(true);

        if (i == 0)
            button->setChecked(true);

        if (m_probeList[i] == 15)
            button->setDisabled(true);

        connect(button, &QPushButton::clicked, this, [this]{
            QPushButton* button = static_cast<QPushButton*>(sender());
            int port = button->property("port").toInt();
            if (m_currentPort != port)
                switchProbe(port);
        });
        layout->addWidget(button);
        buttonGroup->addButton(button);
    }

    return groupBox;
}

void ClientWidget::switchProbe(const int &port)
{
    for (int i = 0; i < m_probeList.size(); ++i)
        m_client->legacyFProbeType(i, m_probeList.at(i));
    m_client->legacySetImageProcess(1);
    m_client->legacySetProbePOS(port);
    m_client->legacySetPwifBuffms(0);
    m_client->legacySetScanMode(0);
    m_client->legacySetExamTypeID(getExamTypeId(m_probeList.at(port)));
    m_client->legacyStart();
}