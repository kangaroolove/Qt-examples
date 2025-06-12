#pragma once

#include <QObject>

class KeyEventHandler : public QObject {
    Q_OBJECT
public:
    static KeyEventHandler *getInstance();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    KeyEventHandler();
    ~KeyEventHandler();

    bool m_pressedAltAndF4;
};