#pragma once

#include <QWidget>
#include "Classes.h"

class QLabel;
class QPushButton;
class QComboBox;
class QTextEdit;
class QSpinBox;
class QHBoxLayout;
class QThread;
class SerialPortWorker;
class SerialPortThread;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
signals:
    void sendMessage(const QString& message, const bool& useHex);
    void openSerialPort(const SerialPortInfo& info, bool& result);
private slots:
    void onConnectButtonClicked();
    void onSendClearButtonClicked();
    void onResponseClearButtonClicked();
    void onSendByAsciiButtonClicked();
    void onSendByHexButtonClicked();
    void receiveMessage(const QString& message);
private:
    void initGui();
    void readSerialPort();
    void createLeftLayout();
    void createRightLayout();
    void initSetting();
    void initBaudRates();
    void initDataBits();
    void initFlowControl();
    void initParities();
    void initStopBits();
    void initPinoutSignals();
    void initConnections();
    void setButtonsEnable(const bool& enable);
    void initWorker();
    SerialPortInfo getSerialPortInfo();

    QLabel* m_serialPortLabel;
    QLabel* m_baudRateLabel;
    QLabel* m_dataBitsLabel;
    QLabel* m_flowControlLabel;
    QLabel* m_parityLabel;
    QLabel* m_stopBitsLabel;
    QLabel* m_pinoutSignalLabel;
    QLabel* m_responseLabel;
    QLabel* m_sendLabel;

    QComboBox* m_serialPortComboBox;
    QComboBox* m_baudRateComboBox;
    QComboBox* m_dataBitsComboBox;
    QComboBox* m_flowControlComboBox;
    QComboBox* m_parityComboBox;
    QComboBox* m_stopBitsComboBox;
    QComboBox* m_pinoutSignalComboBox;
    QHBoxLayout* m_mainLayout;

    QPushButton* m_connectButton;
    QPushButton* m_responseClearButton;
    QPushButton* m_sendClearButton;
    QPushButton* m_sendByAsciiButton;
    QPushButton* m_sendByHexButton;

    QTextEdit* m_responseTextEdit;
    QTextEdit* m_sendTextEdit;

    QThread* m_serialPortThread;
    SerialPortWorker* m_serialPortWorker;

    std::vector<QSerialPort::BaudRate> m_baudRates;
    std::vector<QSerialPort::DataBits> m_dataBits;
    std::map<QSerialPort::FlowControl, QString> m_flowControl;
    std::map<QSerialPort::Parity, QString> m_parities;
    std::map<QSerialPort::StopBits, QString> m_stopBits;
    std::map<QSerialPort::PinoutSignal, QString> m_pinoutSignal;
};
