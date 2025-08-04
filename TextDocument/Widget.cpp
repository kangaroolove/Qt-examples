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

    QTextTableCell companyLogoCell = table->cellAt(0, 0);
    cursor.setPosition(companyLogoCell.firstPosition());
    QImage companyLogo("C:/Users/q3514/Desktop/HTML/companyLogo.png");
    cursor.insertImage(companyLogo.scaled(200, 200, Qt::KeepAspectRatio));

    QTextBlockFormat companyLogoBlockFormat;
    companyLogoBlockFormat.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(companyLogoBlockFormat);

    QTextTableCell hospitalLogoCell = table->cellAt(0, 1);
    cursor.setPosition(hospitalLogoCell.firstPosition());
    QImage hospitalLogo("C:/Users/q3514/Desktop/HTML/hospitalLogo.png");
    cursor.insertImage(hospitalLogo.scaled(200, 200, Qt::KeepAspectRatio));

    QTextBlockFormat hospitalLogoBlockFormat;
    hospitalLogoBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(hospitalLogoBlockFormat);

    QTextTableCell hospitalInfoCell = table->cellAt(0, 2);
    cursor.setPosition(hospitalInfoCell.firstPosition());

    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignRight);
    cursor.setBlockFormat(blockFormat);

    // Insert the text
    cursor.insertText("Tan Tock Seng Hospital\n");
    cursor.insertBlock();
    cursor.insertText("11 Jln Tan Tock Seng,\n");
    cursor.insertBlock();
    cursor.insertText("Singapore 308433\n");
    cursor.insertBlock();
    cursor.insertText("+65 6256 6011");

    cursor.movePosition(QTextCursor::NextBlock);

    blockFormat.setAlignment(Qt::AlignCenter);  // Horizontal center
    cursor.setBlockFormat(blockFormat);
    cursor.insertText("Prostate Biopsy Report");
}