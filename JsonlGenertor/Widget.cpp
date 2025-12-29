#include "Widget.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QUuid>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_generateButton(new QPushButton("Generate", this)),
      m_textEdit(new QTextEdit(this)),
      m_dirLineEdit(new QLineEdit(this)),
      m_dirChooseButton(new QPushButton("Choose file")) {
    initGui();
    bindConnections();
}

void Widget::onDirChooseButtonClicked() {
    auto filePath = QFileDialog::getOpenFileName(this, "Choose File");
    if (filePath.isEmpty()) {
        QMessageBox::critical(this, "error", "Please select a file first!");
        return;
    }

    m_dirLineEdit->setText(filePath);
}

void Widget::initGui() {
    auto layout = new QVBoxLayout(this);

    auto dirLayout = new QHBoxLayout();
    dirLayout->addWidget(m_dirLineEdit);
    dirLayout->addWidget(m_dirChooseButton);

    layout->addLayout(dirLayout);
    layout->addWidget(m_textEdit);
    layout->addWidget(m_generateButton);
    resize(800, 600);
}

void Widget::bindConnections() {
    connect(m_generateButton, &QPushButton::clicked, this,
            &Widget::onGenerateButtonClicked);
    connect(m_dirChooseButton, &QPushButton::clicked, this,
            &Widget::onDirChooseButtonClicked);
}

void Widget::onGenerateButtonClicked() {
    if (m_textEdit->toPlainText().isEmpty()) return;

    QFile file("D:/work/history/train.jsonl");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QMessageBox::critical(this, "error", "Open file failed");
        return;
    }

    QJsonObject object;
    object["uuid"] = QUuid::createUuid().toString(QUuid::WithoutBraces);
    object["text"] = m_textEdit->toPlainText();

    QJsonDocument doc(object);
    file.write(doc.toJson(QJsonDocument::Compact));
    file.write("\n");
    m_textEdit->clear();
}
