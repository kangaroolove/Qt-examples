#include "widget.h"
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QSerialPortInfo>
#include <QFile>
#include "SerialPortThread.h"

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


    , m_responseLabel(new QLabel("Response:"))
    , m_responseTextEdit(new QTextEdit())
    , m_serialNameComboBox(new QComboBox())
    , m_waitTimeSpinBox(new QSpinBox())
    , m_connectButton(new QPushButton("Connect"))
    , m_sendLabel(new QLabel("Send:"))
    , m_sendTextEdit(new QTextEdit())
    , m_sendButton(new QPushButton("Send"))
    , m_serialPortThread(new SerialPortThread())
{
    initGui();
    readSerialPort();
}

Widget::~Widget()
{
    delete m_serialPortThread;
}

void Widget::initGui()
{
    QGridLayout* layout = new QGridLayout(this);
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

    #if 0
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_serialNameLabel, 0, 0);
    layout->addWidget(m_serialNameComboBox, 0, 1);
    layout->addWidget(m_connectButton, 0, 2);
    layout->addWidget(m_waitTimeLabel, 1, 0);
    layout->addWidget(m_waitTimeSpinBox, 1, 1);
    layout->addWidget(m_sendButton, 1, 2);
    layout->addWidget(m_sendLabel, 2, 0);
    layout->addWidget(m_sendTextEdit, 3, 0, 1, 2);
    layout->addWidget(m_responseLabel, 4, 0);
    layout->addWidget(m_responseTextEdit, 5, 0, 1, 2);

    m_waitTimeSpinBox->setMinimum(0);
    m_waitTimeSpinBox->setMaximum(10000);
    m_waitTimeSpinBox->setValue(1000);

    connect(m_connectButton, &QPushButton::clicked, this, [this]{
        QString portName = m_serialNameComboBox->currentText();
        if (portName.isEmpty())
            return;

        int waitTime = m_waitTimeSpinBox->value();
        
        m_connectButton->setEnabled(false);
        m_connectButton->setText("Connected");

        m_serialPortThread->connectPort(portName, waitTime);
    });

    connect(m_serialPortThread, &SerialPortThread::receiveMessage, this, [this](const QString& message){
        m_responseTextEdit->append(message);
    }, Qt::QueuedConnection);

    connect(m_sendButton, &QPushButton::clicked, this, [this]{
        QString text = m_sendTextEdit->toPlainText();
        if (text.isEmpty())
            return;

        m_serialPortThread->sendMessage(text);
    });
    #endif

    this->resize(400, 300);
}

void Widget::readSerialPort()
{
    m_serialNameComboBox->clear();
    auto ports = QSerialPortInfo::availablePorts();
    for (auto it = ports.begin(); it != ports.end(); ++it)
        m_serialNameComboBox->addItem((*it).portName());
}
