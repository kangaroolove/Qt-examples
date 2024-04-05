#pragma once

#include <QWidget>

class QTextEdit;
class QPushButton;
class DaqcClient;
class QLabel;

class ClientWidget : public QWidget
{
public:
    ClientWidget(QWidget* parent = nullptr);
    ~ClientWidget();
private slots:
    void onInitButtonClicked();
    void onAcuiButtonClicked();
    void onDualModeButtonClicked(bool clicked);

private:
    void initGui();
    void bindConnections();

    QPushButton* m_sendButton;
    QPushButton* m_initButton;
    QPushButton* m_acuiButton;
    QPushButton* m_dualModeButton;
    QLabel* m_acuiLabel;
    DaqcClient* m_client;
    QLabel* m_imageLabel;
    QLabel* m_imageLabel2;
};