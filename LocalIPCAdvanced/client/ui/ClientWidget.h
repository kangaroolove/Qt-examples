#pragma once

#include <QWidget>

class QTextEdit;
class QPushButton;
class DaqcClient;
class QLabel;
class QGroupBox;

class ClientWidget : public QWidget
{
    Q_OBJECT
public:
    ClientWidget(QWidget* parent = nullptr);
    ~ClientWidget();
private slots:
    void onInitButtonClicked();
    void onDualModeButtonClicked(bool clicked);
    void switchProbe(const int& port);
private:
    void initGui();
    void bindConnections();
    int getExamTypeId(const int& probeId);
    QGroupBox* getSwitchProbeGroupBox();

    QPushButton* m_testButton;
    QPushButton* m_initButton;
    QPushButton* m_dualModeButton;
    QPushButton* m_startButton;
    QPushButton* m_stopButton;
    DaqcClient* m_client;
    QLabel* m_imageLabel;
    QLabel* m_imageLabel2;
    std::vector<int> m_probeList;
    int m_currentPort;
    // probeId, examTypeId
    std::map<int, int> m_examTypeMap;
};