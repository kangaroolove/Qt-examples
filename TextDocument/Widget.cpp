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

#if 0

    QTextTableFormat headerTableFormat;
    QVector<QTextLength> headerTextLength;
    headerTextLength << QTextLength(QTextLength::PercentageLength, 33.33);
    headerTextLength << QTextLength(QTextLength::PercentageLength, 33.33);
    headerTextLength << QTextLength(QTextLength::PercentageLength, 33.33);
    headerTableFormat.setColumnWidthConstraints(headerTextLength);
    // headerTableFormat.setBorder(0);
    // headerTableFormat.setCellSpacing(0);
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

    QTextTableFormat textWithinLineFormat;
    QVector<QTextLength> textWithinLength;
    textWithinLength << QTextLength(QTextLength::PercentageLength, 40);
    textWithinLength << QTextLength(QTextLength::PercentageLength, 20);
    textWithinLength << QTextLength(QTextLength::PercentageLength, 40);
    textWithinLineFormat.setColumnWidthConstraints(textWithinLength);
    // headerTableFormat.setBorder(0);
    // textWithinLineFormat.setCellSpacing(0);
    // auto textTable = cursor.insertTable(1, 3, textWithinLineFormat);
    // textWithinLineFormat.setTopMargin(0);

    auto textTable = cursor.insertTable(1, 3, textWithinLineFormat);

    QTextTableCell cell = textTable->cellAt(0, 0);
    cursor.setPosition(cell.firstPosition());

    QTextFrameFormat lineFormat;
    lineFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    lineFormat.setHeight(0);
    lineFormat.setBackground(QBrush(Qt::black));
    lineFormat.setBorder(0);
    lineFormat.setPadding(0);
    lineFormat.setMargin(0);
    cursor.insertFrame(lineFormat);

    cursor.setPosition(textTable->cellAt(0, 1).firstPosition());
    auto format = textTable->cellAt(0, 1).format();
    format.setVerticalAlignment(QTextCharFormat::AlignMiddle);
    textTable->cellAt(0, 1).setFormat(format);
    cursor.setBlockFormat(blockFormat);
    cursor.insertText("Biopsy Summary");

    cursor.setPosition(textTable->cellAt(0, 2).firstPosition());
    cursor.insertFrame(lineFormat);


    // Optional: Set table format (e.g., borders, alignment)
    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);  // Thin border around cells
    tableFormat.setCellPadding(5);
    tableFormat.setCellSpacing(0);
    // tableFormat.setAlignment(Qt::AlignCenter);
    QVector<QTextLength> columnWidths;
    columnWidths << QTextLength(QTextLength::PercentageLength, 25)   // Label 1
                 << QTextLength(QTextLength::PercentageLength, 25)   // Value 1
                 << QTextLength(QTextLength::PercentageLength, 25)   // Label 2
                 << QTextLength(QTextLength::PercentageLength, 25);  // Value 2
    tableFormat.setColumnWidthConstraints(columnWidths);

    // Insert 4x4 table
    QTextTable* table = cursor.insertTable(4, 4, tableFormat);

    // Optional: Char format for text (e.g., bold labels)
    QTextCharFormat labelFormat;
    labelFormat.setFontWeight(QFont::Bold);

    // Row 0: Name and value, leave last two cells empty
    {
        QTextCursor cellCursor = table->cellAt(0, 0).firstCursorPosition();
        cellCursor.insertText("Name", labelFormat);
    }
    {
        QTextCursor cellCursor = table->cellAt(0, 1).firstCursorPosition();
        cellCursor.insertText("Erick Lee");
    }
    // Columns 2 and 3 remain empty

    // Row 1
    {
        QTextCursor cellCursor = table->cellAt(1, 0).firstCursorPosition();
        cellCursor.insertText("Case ID", labelFormat);
    }
    {
        QTextCursor cellCursor = table->cellAt(1, 1).firstCursorPosition();
        cellCursor.insertText("25");
    }
    {
        QTextCursor cellCursor = table->cellAt(1, 2).firstCursorPosition();
        cellCursor.insertText("Gender", labelFormat);
    }
    {
        QTextCursor cellCursor = table->cellAt(1, 3).firstCursorPosition();
        cellCursor.insertText("Male");
    }

    // Row 2
    {
        QTextCursor cellCursor = table->cellAt(2, 0).firstCursorPosition();
        cellCursor.insertText("MRN/PIN", labelFormat);
    }
    {
        QTextCursor cellCursor = table->cellAt(2, 1).firstCursorPosition();
        cellCursor.insertText("J1122334K");
    }
    {
        QTextCursor cellCursor = table->cellAt(2, 2).firstCursorPosition();
        cellCursor.insertText("Date of Birth", labelFormat);
    }
    {
        QTextCursor cellCursor = table->cellAt(2, 3).firstCursorPosition();
        cellCursor.insertText("1971-06-03");
    }

    // Row 3
    {
        QTextCursor cellCursor = table->cellAt(3, 0).firstCursorPosition();
        cellCursor.insertText("Age", labelFormat);
    }
    {
        QTextCursor cellCursor = table->cellAt(3, 1).firstCursorPosition();
        cellCursor.insertText("54");
    }
    {
        QTextCursor cellCursor = table->cellAt(3, 2).firstCursorPosition();
        cellCursor.insertText("Exam Date", labelFormat);
    }
    {
        QTextCursor cellCursor = table->cellAt(3, 3).firstCursorPosition();
        cellCursor.insertText("2025-06-30");
    }

    table->mergeCells(0, 1, 1, 3);
#endif

    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);  // Thin border around cells
    tableFormat.setCellPadding(5);
    tableFormat.setCellSpacing(0);
    tableFormat.setAlignment(Qt::AlignLeft);
    QVector<QTextLength> columnWidths;
    columnWidths << QTextLength(QTextLength::PercentageLength,
                                33)  // Biopsy Type
                 << QTextLength(QTextLength::PercentageLength, 33)  // Exam Part
                 << QTextLength(QTextLength::PercentageLength,
                                34);  // PSA Value
    tableFormat.setColumnWidthConstraints(columnWidths);

    QTextBlockFormat centerFormat;
    centerFormat.setAlignment(Qt::AlignCenter);

    // Insert 2x3 table
    QTextTable* table = cursor.insertTable(2, 3, tableFormat);

    // Optional: Char format for headers (e.g., bold)
    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::Bold);

    // Row 0: Headers
    {
        QTextCursor cellCursor = table->cellAt(0, 0).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("Biopsy Type", headerFormat);
    }
    {
        QTextCursor cellCursor = table->cellAt(0, 1).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("Exam Part", headerFormat);
    }
    {
        QTextCursor cellCursor = table->cellAt(0, 2).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("PSA Value", headerFormat);
    }

    // Row 1: Data
    {
        QTextCursor cellCursor = table->cellAt(1, 0).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("Ultrasound");
    }
    {
        QTextCursor cellCursor = table->cellAt(1, 1).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("Prostate");
    }
    {
        QTextCursor cellCursor = table->cellAt(1, 2).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("4.5 ng/mL");
    }
}
