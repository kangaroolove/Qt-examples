#include "HoverDialog.h"

#include <QHBoxLayout>
#include <QPushButton>

HoverDialog::HoverDialog(QWidget* parent)
    : QDialog(parent), m_button(new QPushButton("Click")) {
    initGui();
}

void HoverDialog::initGui() {
    m_button->setFixedSize(90, 90);

    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addStretch();
    layout->addWidget(m_button);
    layout->addStretch();

    resize(800, 90);
}
