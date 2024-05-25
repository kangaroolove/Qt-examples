#pragma once

#include <QWidget>

class QStateMachine;
class QPushButton;
class QLabel;

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
private:
    void initGui();
    void bindConnections();
    void initStateMachine();
    
    QStateMachine* m_stateMachine;
    QPushButton* m_btnS1;
    QPushButton* m_btnS2;
    QPushButton* m_btnS3;
    QLabel* m_label;
};