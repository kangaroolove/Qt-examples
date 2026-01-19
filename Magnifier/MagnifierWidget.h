#pragma once

#include <QLabel>

class MagnifierWidget : public QLabel {
    Q_OBJECT
public:
    MagnifierWidget(QWidget *parent = nullptr);
    QSize getViewportSize() const;
    QSize getZoomSize() const;
    void setZoomFactor(const double& factor);

private:
    QSize m_viewportSize;
    double m_zoomFactor;
};