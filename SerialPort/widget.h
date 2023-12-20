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

    QLabel* m_serialNameLabel;
    QLabel* m_waitTimeLabel;
    QLabel* m_responseLabel;
    QPushButton* m_connectButton;
    QComboBox* m_serialNameComboBox;
    QTextEdit* m_responseTextEdit;
    QSpinBox* m_waitTimeSpinBox;
    QLabel* m_sendLabel;
    QTextEdit* m_sendTextEdit;
    QPushButton* m_sendButton;
    SerialPortThread* m_serialPortThread;
};
#endif // WIDGET_H
