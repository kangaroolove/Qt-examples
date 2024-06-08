#include "Dialog.h"
#include <QHBoxLayout>
#include <QPushButton>

Dialog::Dialog(QWidget* parent) 
    : QDialog(parent)
{
    auto layout = new QHBoxLayout(this);
    auto acceptBtn = new QPushButton("Accept", this);
    auto rejectBtn = new QPushButton("Reject", this);
    layout->addWidget(acceptBtn);
    layout->addWidget(rejectBtn);

    connect(acceptBtn, &QPushButton::clicked, this, &Dialog::accept);
    connect(rejectBtn, &QPushButton::clicked, this, &Dialog::reject);
    resize(400, 200);
}

Dialog::~Dialog()
{

}
