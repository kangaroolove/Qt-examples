#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QLabel;
class QPushButton;
class QComboBox;
class QTextEdit;
class QSpinBox;
class SerialPortThread;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void initGui();
    void readSerialPort();

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

    QLabel* m_responseLabel;
    QPushButton* m_connectButton;
    QTextEdit* m_responseTextEdit;
    QLabel* m_sendLabel;
    QTextEdit* m_sendTextEdit;
    QPushButton* m_sendButton;
    SerialPortThread* m_serialPortThread;
};
#endif // WIDGET_H
