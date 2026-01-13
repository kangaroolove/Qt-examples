#pragma once

#include <QLabel>

class MagnifierWidget : public QLabel {
    Q_OBJECT
public:
    MagnifierWidget(QWidget *parent = nullptr);
    QSize getZoomSize() const;

private:
    QSize m_zoomSize;
    double m_zoomFactor;
};