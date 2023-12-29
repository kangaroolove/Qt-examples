#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>

class QLabel;
class QPushButton;
class QComboBox;
class QTextEdit;
class QSpinBox;
class SerialPortThread;
class QHBoxLayout;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
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

    QLabel* m_serialPortLabel;
    QLabel* m_baudRateLabel;
    QLabel* m_dataBitsLabel;
    QLabel* m_flowControlLabel;
    QLabel* m_parityLabel;
    QLabel* m_stopBitsLabel;
    QLabel* m_pinoutSignalLabel;
    QComboBox* m_serialPortComboBox;
    QComboBox* m_baudRateComboBox;
    QComboBox* m_dataBitsComboBox;
    QComboBox* m_flowControlComboBox;
    QComboBox* m_parityComboBox;
    QComboBox* m_stopBitsComboBox;
    QComboBox* m_pinoutSignalComboBox;
    QHBoxLayout* m_mainLayout;
    QLabel* m_responseLabel;
    QPushButton* m_connectButton;
    QPushButton* m_responseClearButton;
    QTextEdit* m_responseTextEdit;
    QLabel* m_sendLabel;
    QTextEdit* m_sendTextEdit;
    QPushButton* m_sendButton;
    QPushButton* m_sendClearButton;
    QPushButton* m_sendByAscii;
    QPushButton* m_sendByHex;
    SerialPortThread* m_serialPortThread;
    std::vector<QSerialPort::BaudRate> m_baudRates;
    std::vector<QSerialPort::DataBits> m_dataBits;
    std::map<QSerialPort::FlowControl, QString> m_flowControl;
    std::map<QSerialPort::Parity, QString> m_parities;
    std::map<QSerialPort::StopBits, QString> m_stopBits;
};
#endif // WIDGET_H
