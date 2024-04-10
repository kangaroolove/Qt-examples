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
    void timeout();
private:
    void initGui();
    void bindConnections();
    int getExamTypeId(const int& probeId);
    QGroupBox* getSwitchProbeGroupBox();
    QGroupBox* getBGainGroupBox();
    void startServer();

    QPushButton* m_testButton;
    QPushButton* m_initButton;
    QPushButton* m_dualModeButton;
    QPushButton* m_startButton;
    QPushButton* m_stopButton;
    QPushButton* m_increaseBGainButton;
    QPushButton* m_decreaseBGainButton;
    DaqcClient* m_client;
    QLabel* m_imageLabel;
    QLabel* m_imageLabel2;
    QLabel* m_fpsLabel;
    std::vector<int> m_probeList;
    int m_currentPort;
    // probeId, examTypeId
    std::map<int, int> m_examTypeMap;
    QTimer* m_timer;
};