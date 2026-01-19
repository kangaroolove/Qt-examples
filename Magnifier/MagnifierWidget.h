#pragma once

#include <QLabel>

class MagnifierWidget : public QLabel {
    Q_OBJECT
public:
    MagnifierWidget(QWidget *parent = nullptr);
    QSize getViewportSize() const;
    QSize getZoomSize() const;
    void setZoomFactor(const double& factor);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QSize m_viewportSize;
    double m_zoomFactor;
    bool m_enableMove;
};