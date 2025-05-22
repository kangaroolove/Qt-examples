#include "KeyEventHandler.h"
#include <QCloseEvent>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>

KeyEventHandler::KeyEventHandler() : m_pressedAltAndF4(false) {}

KeyEventHandler::~KeyEventHandler() {}

KeyEventHandler *KeyEventHandler::getInstance() {
    static KeyEventHandler handler;
    return &handler;
}

bool KeyEventHandler::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_F4 ||
            (keyEvent->modifiers() & Qt::AltModifier)) {
            m_pressedAltAndF4 = true;
            event->accept();
            return true;
        }
    } else if (event->type() == QEvent::Close) {
        QCloseEvent *closeEvent = static_cast<QCloseEvent *>(event);
        if (m_pressedAltAndF4) {
            closeEvent->ignore();
            return true;
        }
    } else if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Alt) {
            m_pressedAltAndF4 = false;
            event->accept();
            return true;
        }
    }

return QObject::eventFilter(obj, event);
}
