#pragma once

#include <QDialog>

class QPushButton;
class QObject;
class QEvent;

class HoverDialog : public QDialog
{
public:
    HoverDialog(QWidget* parent = nullptr);
private:
    void initGui();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

    QPushButton* m_button;
    QWidget* m_parent;
};