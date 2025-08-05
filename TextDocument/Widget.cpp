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
    headerTextLength << QTextLength(QTextLength::PercentageLength, 33.33);
    headerTextLength << QTextLength(QTextLength::PercentageLength, 33.33);
    headerTextLength << QTextLength(QTextLength::PercentageLength, 33.33);
    headerTableFormat.setColumnWidthConstraints(headerTextLength);
    headerTableFormat.setBorder(0);
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
    QTextCharFormat hospitalNameFormat;
    hospitalNameFormat.setFontWeight(QFont::Bold);

    QTextCharFormat emptyCharFormat;

    cursor.insertText("Tan Tock Seng Hospital\n", hospitalNameFormat);
    cursor.insertBlock();
    cursor.insertText("11 Jln Tan Tock Seng,\n", emptyCharFormat);
    cursor.insertBlock();
    cursor.insertText("Singapore 308433\n");
    cursor.insertBlock();
    cursor.insertText("+65 6256 6011");

    cursor.movePosition(QTextCursor::NextBlock);

    QTextCharFormat titleCharFormat;
    titleCharFormat.setFontPointSize(24);
    titleCharFormat.setFontWeight(QFont::Bold);
    blockFormat.setAlignment(Qt::AlignCenter);  // Horizontal center
    cursor.setBlockFormat(blockFormat);
    cursor.insertText("Prostate Biopsy Report", titleCharFormat);
#if 0

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

    //
    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);  // Thin border around cells
    tableFormat.setCellPadding(5);
    tableFormat.setCellSpacing(0);
    tableFormat.setAlignment(
        Qt::AlignCenter);  // Center the entire table in the document (optional)
    QVector<QTextLength> columnWidths;
    columnWidths << QTextLength(QTextLength::PercentageLength, 33)  // Model
                 << QTextLength(QTextLength::PercentageLength,
                                33)  // Volume (cc)
                 << QTextLength(QTextLength::PercentageLength, 34);  // PI-RADS
    tableFormat.setColumnWidthConstraints(columnWidths);

    // Insert 9x3 table
    QTextTable* table = cursor.insertTable(9, 3, tableFormat);

    // Optional: Char format for headers (e.g., bold)
    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::Bold);

    // Block format for center alignment (applied to each cell)
    QTextBlockFormat centerFormat;
    centerFormat.setAlignment(Qt::AlignCenter);

    // Row 0: Headers
    {
        QTextCursor cellCursor = table->cellAt(0, 0).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("Model", headerFormat);
    }
    {
        QTextCursor cellCursor = table->cellAt(0, 1).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("Volume (cc)", headerFormat);
    }
    {
        QTextCursor cellCursor = table->cellAt(0, 2).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("PI-RADS", headerFormat);
    }

    // Row 1: Prostate
    {
        QTextCursor cellCursor = table->cellAt(1, 0).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("Prostate");
    }
    {
        QTextCursor cellCursor = table->cellAt(1, 1).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("10");
    }
    {
        QTextCursor cellCursor = table->cellAt(1, 2).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("5");
    }

    // Row 2: ROI 1
    {
        QTextCursor cellCursor = table->cellAt(2, 0).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("ROI 1");
    }
    {
        QTextCursor cellCursor = table->cellAt(2, 1).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("3");
    }
    {
        QTextCursor cellCursor = table->cellAt(2, 2).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("2");
    }

    // Row 3: ROI 2
    {
        QTextCursor cellCursor = table->cellAt(3, 0).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("ROI 2");
    }
    {
        QTextCursor cellCursor = table->cellAt(3, 1).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("2");
    }
    {
        QTextCursor cellCursor = table->cellAt(3, 2).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("3");
    }

    // Row 4: ROI 3
    {
        QTextCursor cellCursor = table->cellAt(4, 0).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("ROI 3");
    }
    {
        QTextCursor cellCursor = table->cellAt(4, 1).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("4");
    }
    {
        QTextCursor cellCursor = table->cellAt(4, 2).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("1");
    }

    // Row 5: ROI 4
    {
        QTextCursor cellCursor = table->cellAt(5, 0).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("ROI 4");
    }
    {
        QTextCursor cellCursor = table->cellAt(5, 1).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("2");
    }
    {
        QTextCursor cellCursor = table->cellAt(5, 2).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("5");
    }

    // Row 6: ROI 5
    {
        QTextCursor cellCursor = table->cellAt(6, 0).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("ROI 5");
    }
    {
        QTextCursor cellCursor = table->cellAt(6, 1).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("5");
    }
    {
        QTextCursor cellCursor = table->cellAt(6, 2).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("4");
    }

    // Row 7: ROI 6
    {
        QTextCursor cellCursor = table->cellAt(7, 0).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("ROI 6");
    }
    {
        QTextCursor cellCursor = table->cellAt(7, 1).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("3");
    }
    {
        QTextCursor cellCursor = table->cellAt(7, 2).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("3");
    }

    // Row 8: ROI 7
    {
        QTextCursor cellCursor = table->cellAt(8, 0).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("ROI 7");
    }
    {
        QTextCursor cellCursor = table->cellAt(8, 1).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("2");
    }
    {
        QTextCursor cellCursor = table->cellAt(8, 2).firstCursorPosition();
        cellCursor.setBlockFormat(centerFormat);
        cellCursor.insertText("2");
    }


    // Insert "Remarks:" in bold
    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    cursor.setCharFormat(boldFormat);
    cursor.insertText("Remarks:");

    // Set frame format for the blank box
    QTextFrameFormat frameFormat;
    frameFormat.setBorder(1);  // Border thickness
    frameFormat.setBorderStyle(
        QTextFrameFormat::BorderStyle_Solid);  // Solid line border
    frameFormat.setPadding(0);                 // Inner padding
    frameFormat.setWidth(
        QTextLength(QTextLength::PercentageLength, 100));  // Full width
    frameFormat.setHeight(
        40);  // Fixed height for the box (adjust for single/multi-line)

    // Insert the frame
    cursor.insertFrame(frameFormat);


    // Biospy Summary
    QTextTable *table = cursor.insertTable(3, 5);

    // Populate the first row (headers, preserving the given structure)
    table->cellAt(0, 1).firstCursorPosition().insertText("Target cores");
    table->cellAt(0, 2).firstCursorPosition().insertText("System cores");
    table->cellAt(0, 3).firstCursorPosition().insertText("Total cores done");
    table->cellAt(0, 4).firstCursorPosition().insertText("Total cores skipped");

    // Populate the second row
    table->cellAt(1, 0).firstCursorPosition().insertText("Done");
    table->cellAt(1, 1).firstCursorPosition().insertText("15");
    table->cellAt(1, 2).firstCursorPosition().insertText("24");
    table->cellAt(1, 3).firstCursorPosition().insertText("39");
    table->cellAt(1, 4).firstCursorPosition().insertText("4");

    // Populate the third row (leaving last two cells empty)
    table->cellAt(2, 0).firstCursorPosition().insertText("Skipped");
    table->cellAt(2, 1).firstCursorPosition().insertText("1");
    table->cellAt(2, 2).firstCursorPosition().insertText("3");

    table->mergeCells(1, 3, 2, 1);
    table->mergeCells(1, 4, 2, 1);
    // No insertText for cells 2,3 and 2,4 to keep them empty

    // Optional: Apply basic formatting to the table (e.g., borders)
    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);       // 1-pixel border
    tableFormat.setCellPadding(5);  // Padding inside cells
    table->setFormat(tableFormat);


    QTextTable *table = cursor.insertTable(6, 3);

    // Populate the first row (headers)
    table->cellAt(0, 0).firstCursorPosition().insertText("Target Core");
    table->cellAt(0, 1).firstCursorPosition().insertText("Lesion");
    table->cellAt(0, 2).firstCursorPosition().insertText("Status");

    // Populate the data rows
    table->cellAt(1, 0).firstCursorPosition().insertText("T1");
    table->cellAt(1, 1).firstCursorPosition().insertText("ROI 1");
    table->cellAt(1, 2).firstCursorPosition().insertText("Done");

    table->cellAt(2, 0).firstCursorPosition().insertText("T2");
    table->cellAt(2, 1).firstCursorPosition().insertText("ROI 2");
    table->cellAt(2, 2).firstCursorPosition().insertText("Skipped");

    table->cellAt(3, 0).firstCursorPosition().insertText("T3");
    table->cellAt(3, 1).firstCursorPosition().insertText("ROI 3");
    table->cellAt(3, 2).firstCursorPosition().insertText("Done");

    table->cellAt(4, 0).firstCursorPosition().insertText("T4");
    table->cellAt(4, 1).firstCursorPosition().insertText("ROI 4");
    table->cellAt(4, 2).firstCursorPosition().insertText("Skipped");

    table->cellAt(5, 0).firstCursorPosition().insertText("T5");
    table->cellAt(5, 1).firstCursorPosition().insertText("ROI 5");
    table->cellAt(5, 2).firstCursorPosition().insertText("Done");

    // Insert a table with 6 rows and 3 columns
    QTextTable *table = cursor.insertTable(6, 3);

    // Populate the first row (headers)
    table->cellAt(0, 0).firstCursorPosition().insertText("System Core");
    table->cellAt(0, 1).firstCursorPosition().insertText("Zone");
    table->cellAt(0, 2).firstCursorPosition().insertText("Status");

    // Populate the data rows
    table->cellAt(1, 0).firstCursorPosition().insertText("S1");
    table->cellAt(1, 1).firstCursorPosition().insertText("Right Anterior");
    table->cellAt(1, 2).firstCursorPosition().insertText("Done");

    table->cellAt(2, 0).firstCursorPosition().insertText("S2");
    table->cellAt(2, 1).firstCursorPosition().insertText("Right Posterior");
    table->cellAt(2, 2).firstCursorPosition().insertText("Skipped");

    table->cellAt(3, 0).firstCursorPosition().insertText("S3");
    table->cellAt(3, 1).firstCursorPosition().insertText("Left Anterior");
    table->cellAt(3, 2).firstCursorPosition().insertText("Done");

    table->cellAt(4, 0).firstCursorPosition().insertText("S4");
    table->cellAt(4, 1).firstCursorPosition().insertText("Right Mid");
    table->cellAt(4, 2).firstCursorPosition().insertText("Skipped");

    table->cellAt(5, 0).firstCursorPosition().insertText("S5");
    table->cellAt(5, 1).firstCursorPosition().insertText("Left Posterior");
    table->cellAt(5, 2).firstCursorPosition().insertText("Done");
#endif
}
