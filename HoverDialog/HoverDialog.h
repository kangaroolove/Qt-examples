#pragma once

#include <QDialog>

class QPushButton;
class QObject;
class QEvent;

class Content : public QWidget {
    Q_OBJECT
public:
    Content(QWidget* parent = nullptr);

private:
    void initGui();
};

class HoverDialog : public QDialog
{
    Q_OBJECT
public:
    HoverDialog(QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    void initGui();
    void bindConnections();

    QPushButton* m_button;
    QWidget* m_parent;
    Content* m_contentWidget;
};