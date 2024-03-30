#include "Widget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QProcess>
#include <QDebug>
#include <QCoreApplication>
#include <QProcess>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QPushButton* button = new QPushButton("External call", this);
    connect(button, &QPushButton::clicked, this, [this]{
        QString filePath = QCoreApplication::applicationDirPath() + "/testApplication.exe";
        QProcess *process = new QProcess(this);



        // connect(process, &QProcess::started, this, [&process](){
        //     qDebug()<<process->errorString();
        //     qDebug()<<"Starting testApplication is successful";
        // });
        process->start(filePath);
        if (process->waitForStarted())
            qDebug()<<"Starting testApplication is successful";
        else 
            qDebug()<<"Starting testApplication is failed";
    });
    layout->addWidget(button);
    this->resize(400, 300);
}

Widget::~Widget()
{

}