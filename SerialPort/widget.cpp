#include "widget.h"
#include "SerialPortWorker.h"
#include "SerialPortThread.h"
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QSerialPortInfo>
#include <QFile>
#include <QThread>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_serialPortLabel(new QLabel("Serial Port:"))
    , m_baudRateLabel(new QLabel("BaudRate:"))
    , m_dataBitsLabel(new QLabel("DataBits:"))
    , m_flowControlLabel(new QLabel("FlowControl:"))
    , m_parityLabel(new QLabel("Parity:"))
    , m_stopBitsLabel(new QLabel("StopBits:"))
    , m_pinoutSignalLabel(new QLabel("PinoutSignal:"))
    , m_serialPortComboBox(new QComboBox(this))
    , m_baudRateComboBox(new QComboBox(this))
    , m_dataBitsComboBox(new QComboBox(this))
    , m_flowControlComboBox(new QComboBox(this))
    , m_parityComboBox(new QComboBox(this))
    , m_stopBitsComboBox(new QComboBox(this))
    , m_pinoutSignalComboBox(new QComboBox(this))
    , m_mainLayout(new QHBoxLayout(this))
    , m_responseLabel(new QLabel("Response:"))
    , m_responseTextEdit(new QTextEdit())
    , m_connectButton(new QPushButton("Connect"))
    , m_sendLabel(new QLabel("Send:"))
    , m_sendTextEdit(new QTextEdit())
    , m_responseClearButton(new QPushButton("Clear"))
    , m_sendClearButton(new QPushButton("Clear"))
    , m_sendByAsciiButton(new QPushButton("Send By ASCII"))
    , m_sendByHexButton(new QPushButton("Send By Hex"))
    , m_serialPortWorker(new SerialPortWorker)
    , m_serialPortThread(new QThread(this))
    , m_serialPortConnected(false)
{
    initGui();
    initSetting();
    initWorker();
    //initSerialPortThread();
    initConnections();
    readSerialPort();
}

Widget::~Widget()
{
}

void Widget::onSendClearButtonClicked()
{
    m_sendTextEdit->clear();
}

void Widget::onResponseClearButtonClicked()
{
    m_responseTextEdit->clear();
}

void Widget::onSendByAsciiButtonClicked()
{
    emit sendMessage(m_sendTextEdit->toPlainText(), false);
}

void Widget::onSendByHexButtonClicked()
{
    emit sendMessage(m_sendTextEdit->toPlainText(), true);
}

void Widget::receiveMessage(const QString &message)
{
    m_responseTextEdit->append(message);
}

void Widget::onConnectButtonClicked()
{
    if (m_serialPortComboBox->currentText().isEmpty())
    {
        QMessageBox::critical(this, tr("Error"), "There is no serial port");
        return;
    }

    // if (!m_serialPortConnected)
    //     m_serialPortConnected = m_serialPortThread->openSerialPort(getSerialPortInfo());
    // else 
    // {
    //     m_serialPortThread->closeSerialPort();
    //     m_serialPortConnected = false;
    // }

    m_serialPortConnected ? m_connectButton->setText("Disconnect") : m_connectButton->setText("Connect");
    setButtonsEnable(!m_serialPortConnected);
}

void Widget::initGui()
{
    createLeftLayout();
    createRightLayout();
    setButtonsEnable(true);
    this->resize(400, 300);
}

void Widget::readSerialPort()
{
    m_serialPortComboBox->clear();
    auto ports = QSerialPortInfo::availablePorts();
    for (auto it = ports.begin(); it != ports.end(); ++it)
        m_serialPortComboBox->addItem((*it).portName());
}

void Widget::createLeftLayout()
{
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(m_serialPortLabel, 0, 0);
    layout->addWidget(m_baudRateLabel, 1, 0);
    layout->addWidget(m_dataBitsLabel, 2, 0);
    layout->addWidget(m_flowControlLabel, 3, 0);
    layout->addWidget(m_parityLabel, 4, 0);
    layout->addWidget(m_stopBitsLabel, 5, 0);
    layout->addWidget(m_pinoutSignalLabel, 6, 0);

    layout->addWidget(m_serialPortComboBox, 0, 1);
    layout->addWidget(m_baudRateComboBox, 1, 1);
    layout->addWidget(m_dataBitsComboBox, 2, 1);
    layout->addWidget(m_flowControlComboBox, 3, 1);
    layout->addWidget(m_parityComboBox, 4, 1);
    layout->addWidget(m_stopBitsComboBox, 5, 1);
    layout->addWidget(m_pinoutSignalComboBox, 6, 1);

    layout->addWidget(m_connectButton, 7, 0, 1, 2);
    layout->setRowStretch(8, 1);

    m_mainLayout->addLayout(layout);
}

void Widget::createRightLayout()
{
    auto layout = new QVBoxLayout();
    layout->addWidget(m_responseLabel);
    layout->addWidget(m_responseTextEdit);
    layout->addWidget(m_responseClearButton);
    layout->addWidget(m_sendLabel);
    layout->addWidget(m_sendTextEdit);
    
    auto buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(m_sendClearButton);
    buttonsLayout->addWidget(m_sendByHexButton);
    buttonsLayout->addWidget(m_sendByAsciiButton);
    layout->addLayout(buttonsLayout);

    m_mainLayout->addLayout(layout);
}

void Widget::initSetting()
{
    initBaudRates();
    initDataBits();
    initFlowControl();
    initParities();
    initStopBits();
    initPinoutSignals();
}

void Widget::initBaudRates()
{
    m_baudRates = {
        QSerialPort::Baud1200,
        QSerialPort::Baud2400,
        QSerialPort::Baud4800,
        QSerialPort::Baud9600,
        QSerialPort::Baud19200,
        QSerialPort::Baud38400,
        QSerialPort::Baud57600,
        QSerialPort::Baud115200
    };

    for (auto it = m_baudRates.begin(); it != m_baudRates.end(); it++)
        m_baudRateComboBox->insertItem(std::distance(m_baudRates.begin(), it), QString::number(*it));
}

void Widget::initDataBits()
{
    m_dataBits = {
        QSerialPort::Data5,
        QSerialPort::Data6,
        QSerialPort::Data7,
        QSerialPort::Data8,
    };

    for (auto it = m_dataBits.begin(); it != m_dataBits.end(); it++)
        m_dataBitsComboBox->insertItem(std::distance(m_dataBits.begin(), it), QString::number(*it));

    m_dataBitsComboBox->setCurrentText(QString::number(m_dataBits.back()));
}

void Widget::initFlowControl()
{
    m_flowControl = {
        { QSerialPort::NoFlowControl, tr("No Flow Control") },
        { QSerialPort::SoftwareControl, tr("Software Control") },
        { QSerialPort::HardwareControl, tr("Hardware Control") }
    };

    for (auto it = m_flowControl.begin(); it != m_flowControl.end(); it++)
        m_flowControlComboBox->insertItem(std::distance(m_flowControl.begin(), it), it->second, it->first);
}

void Widget::initParities()
{
    m_parities = {
        { QSerialPort::NoParity, tr("No Parity") },
        { QSerialPort::EvenParity, tr("Even Parity") },
        { QSerialPort::OddParity, tr("Odd Parity") },
        { QSerialPort::SpaceParity, tr("Space Parity") },
        { QSerialPort::MarkParity, tr("Mark Parity") }
    };

    for (auto it = m_parities.begin(); it != m_parities.end(); it++)
        m_parityComboBox->insertItem(std::distance(m_parities.begin(), it), it->second, it->first);
}

void Widget::initStopBits()
{
    m_stopBits = {
        { QSerialPort::OneStop, tr("One Stop") },
        { QSerialPort::OneAndHalfStop, tr("One And Half Stop") },
        { QSerialPort::TwoStop, tr("Two Stop") },
    };

    for (auto it = m_stopBits.begin(); it != m_stopBits.end(); it++)
        m_stopBitsComboBox->insertItem(std::distance(m_stopBits.begin(), it), it->second, it->first);
}

void Widget::initPinoutSignals()
{
    m_pinoutSignal = {
        { QSerialPort::NoSignal, tr("No Signal") },
        { QSerialPort::TransmittedDataSignal, tr("Transmitted Data Signal") },
        { QSerialPort::ReceivedDataSignal, tr("Received Data Signal") },
        { QSerialPort::DataTerminalReadySignal, tr("Data Terminal Ready Signal") },
        { QSerialPort::DataCarrierDetectSignal, tr("Data Carrier Detect Signal") },
        { QSerialPort::DataSetReadySignal, tr("Data Set Ready Signal") },
        { QSerialPort::RingIndicatorSignal, tr("Ring Indicator Signal") },
        { QSerialPort::RequestToSendSignal, tr("Request To Send Signal") },
        { QSerialPort::ClearToSendSignal, tr("Clear To Send Signal") },
        { QSerialPort::SecondaryTransmittedDataSignal, tr("Secondary Transmitted Data Signal") },
        { QSerialPort::SecondaryReceivedDataSignal, tr("Secondary Received Data Signal") }
    };

    for (auto it = m_pinoutSignal.begin(); it != m_pinoutSignal.end(); it++)
        m_pinoutSignalComboBox->insertItem(std::distance(m_pinoutSignal.begin(), it), it->second, it->first);
}

void Widget::initConnections()
{
    connect(m_connectButton, &QPushButton::clicked, this, &Widget::onConnectButtonClicked);
    connect(m_sendClearButton, &QPushButton::clicked, this, &Widget::onSendClearButtonClicked);
    connect(m_responseClearButton, &QPushButton::clicked, this, &Widget::onResponseClearButtonClicked);
    connect(m_sendByHexButton, &QPushButton::clicked, this, &Widget::onSendByHexButtonClicked);
    connect(m_sendByAsciiButton, &QPushButton::clicked, this, &Widget::onSendByAsciiButtonClicked);
}

void Widget::setButtonsEnable(const bool &enable)
{
    m_serialPortComboBox->setEnabled(enable);
    m_baudRateComboBox->setEnabled(enable);
    m_dataBitsComboBox->setEnabled(enable);
    m_flowControlComboBox->setEnabled(enable);
    m_parityComboBox->setEnabled(enable);
    m_stopBitsComboBox->setEnabled(enable);
    m_pinoutSignalComboBox->setEnabled(enable);
    m_sendByAsciiButton->setEnabled(!enable);
    m_sendByHexButton->setEnabled(!enable);
}

void Widget::initWorker()
{
    m_serialPortWorker->moveToThread(m_serialPortThread);
    connect(m_serialPortWorker, &SerialPortWorker::receiveMessage, this, &Widget::receiveMessage);
    connect(this, &Widget::sendMessage, m_serialPortWorker, &SerialPortWorker::sendMessage);
    connect(m_serialPortThread, &QThread::finished, m_serialPortWorker, &QObject::deleteLater);
    m_serialPortThread->start();
}

void Widget::initSerialPortThread()
{
    m_serialPortThread->start();
}

SerialPortInfo Widget::getSerialPortInfo()
{
    SerialPortInfo info;
    info.name = m_serialPortComboBox->currentText();
    info.baudRate = m_baudRates.at(m_baudRateComboBox->currentIndex());
    info.dataBits = m_dataBits.at(m_dataBitsComboBox->currentIndex());
    info.flowControl = (QSerialPort::FlowControl)m_flowControlComboBox->currentData().toInt();
    info.parity = (QSerialPort::Parity)m_parityComboBox->currentData().toInt();
    info.stopBits = (QSerialPort::StopBits)m_stopBitsComboBox->currentData().toInt();

    return info;
}
