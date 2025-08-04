#include "Widget.h"
#include <QDebug>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QTextCursor>
#include <QTextLength>
#include <QTextTableCell>
#include <QTextImageFormat>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    auto layout = new QVBoxLayout(this);
    auto textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    layout->addWidget(textEdit);

    auto document = textEdit->document();
    QTextCursor cursor(document);

    QTextTableFormat headerTableFormat;
    QVector<QTextLength> headerTextLength;
    headerTextLength<< QTextLength(QTextLength::PercentageLength, 33.33);
    headerTextLength<< QTextLength(QTextLength::PercentageLength, 33.33);
    headerTextLength<< QTextLength(QTextLength::PercentageLength, 33.33);
    headerTableFormat.setColumnWidthConstraints(headerTextLength);
    //headerTableFormat.setBorder(0);
    headerTableFormat.setCellSpacing(0);
    auto table = cursor.insertTable(1, 3, headerTableFormat);

    QTextTableCell operatorCell = table->cellAt(0, 0);
    cursor.setPosition(operatorCell.firstPosition());

    QImage companyLogo("C:/Users/q3514/Desktop/HTML/companyLogo.png");
    cursor.insertImage(companyLogo.scaled(200, 200, Qt::KeepAspectRatio));

    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(blockFormat);


}