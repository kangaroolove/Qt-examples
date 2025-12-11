#pragma once

#include <QDialog>

class QPushButton;
class QObject;
class QEvent;

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
};