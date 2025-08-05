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

    auto frame = cursor.currentFrame();
    ReportHeaderInfo headerInfo;
    headerInfo.companyLogo =
        QImage("C:/Users/q3514/Desktop/HTML/companyLogo.png");
    headerInfo.hospitalLogo =
        QImage("C:/Users/q3514/Desktop/HTML/hospitalLogo.png");
    headerInfo.hospitalName = "abc";
    headerInfo.hospitalAddress = "New York";
    headerInfo.hospitalPhone = "123456";

    createReportHeader(cursor, headerInfo);
    createTextWithinLine(cursor, "Patient Information");

    cursor.setPosition(frame->lastPosition());

    ReportPatientInfo patientInfo;
    patientInfo.name = "Erick Lee";
    patientInfo.caseId = "25";
    patientInfo.gender = "Male";
    patientInfo.mrn = "J1122334K";
    patientInfo.dateOfBirth = "1971-06-03";
    patientInfo.age = "54";
    patientInfo.examDate = "2025-06-30";
    createPatientInfoTable(cursor, patientInfo);
    cursor.setPosition(frame->lastPosition());
    createTextWithinLine(cursor, "MRI information");
    cursor.setPosition(frame->lastPosition());
    createBiopsyTypeTable(cursor, 4.5);
    cursor.setPosition(frame->lastPosition());

    ReportBiopsyModelInfo modelInfo;
    modelInfo.piRads = {"5", "2", "3", "1", "5", "4", "3", "2"};
    modelInfo.volumes = {"5", "2", "3", "1", "5", "10", "3", "2"};
    createBiopsyModelTable(cursor, modelInfo);
#if 0
  


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

void Widget::createReportHeader(QTextCursor &cursor,
                                const ReportHeaderInfo &info) {
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 33.33);
    constraints << QTextLength(QTextLength::PercentageLength, 33.33);
    constraints << QTextLength(QTextLength::PercentageLength, 33.33);

    QTextTableFormat tableFormat;
    tableFormat.setColumnWidthConstraints(constraints);
    tableFormat.setBorder(0);
    auto table = cursor.insertTable(1, 3, tableFormat);

    const int logoSize = 200;
    cursor.setPosition(table->cellAt(0, 0).firstPosition());
    cursor.insertImage(
        info.companyLogo.scaled(logoSize, logoSize, Qt::KeepAspectRatio));

    QTextBlockFormat companyLogoBlockFormat;
    companyLogoBlockFormat.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(companyLogoBlockFormat);

    cursor.setPosition(table->cellAt(0, 1).firstPosition());
    cursor.insertImage(
        info.hospitalLogo.scaled(logoSize, logoSize, Qt::KeepAspectRatio));

    QTextBlockFormat hospitalLogoBlockFormat;
    hospitalLogoBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(hospitalLogoBlockFormat);

    cursor.setPosition(table->cellAt(0, 2).firstPosition());

    QTextBlockFormat alignRightFormat;
    alignRightFormat.setAlignment(Qt::AlignRight);
    cursor.setBlockFormat(alignRightFormat);

    QTextCharFormat hospitalNameFormat;
    hospitalNameFormat.setFontWeight(QFont::Bold);

    QTextCharFormat emptyCharFormat;

    cursor.insertText(QString("%1\n").arg(info.hospitalName),
                      hospitalNameFormat);
    cursor.insertBlock();
    cursor.insertText(QString("%1\n").arg(info.hospitalAddress),
                      emptyCharFormat);
    cursor.insertBlock();
    cursor.insertText(info.hospitalPhone);

    cursor.movePosition(QTextCursor::NextBlock);

    QTextCharFormat titleCharFormat;
    titleCharFormat.setFontPointSize(30);
    titleCharFormat.setFontWeight(QFont::Bold);

    QTextBlockFormat alignCenterFormat;
    alignCenterFormat.setAlignment(Qt::AlignCenter);
    cursor.setBlockFormat(alignCenterFormat);

    cursor.insertText("Prostate Biopsy Report", titleCharFormat);
}

void Widget::createTextWithinLine(QTextCursor &cursor, const QString &text) {
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 40);
    constraints << QTextLength(QTextLength::PercentageLength, 20);
    constraints << QTextLength(QTextLength::PercentageLength, 40);
    QTextTableFormat tableFormat;
    tableFormat.setBorder(0);
    tableFormat.setColumnWidthConstraints(constraints);

    auto table = cursor.insertTable(1, 3, tableFormat);
    cursor.setPosition(table->cellAt(0, 0).firstPosition());

    QTextFrameFormat lineFormat;
    lineFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    lineFormat.setHeight(0);
    lineFormat.setBackground(QBrush(Qt::black));
    lineFormat.setBorder(0);
    cursor.insertFrame(lineFormat);

    cursor.setPosition(table->cellAt(0, 1).firstPosition());
    auto cellFormat = table->cellAt(0, 1).format();
    cellFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
    table->cellAt(0, 1).setFormat(cellFormat);

    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignCenter);
    cursor.setBlockFormat(blockFormat);

    QTextCharFormat textFormat;
    textFormat.setFontWeight(QFont::Bold);
    textFormat.setFontPointSize(26.5);
    cursor.insertText(text, textFormat);

    cursor.setPosition(table->cellAt(0, 2).firstPosition());
    cursor.insertFrame(lineFormat);
}

void Widget::createPatientInfoTable(QTextCursor &cursor,
                                    const ReportPatientInfo &info) {
    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellSpacing(0);
    tableFormat.setCellPadding(5);

    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 25)
                << QTextLength(QTextLength::PercentageLength, 25)
                << QTextLength(QTextLength::PercentageLength, 25)
                << QTextLength(QTextLength::PercentageLength, 25);
    tableFormat.setColumnWidthConstraints(constraints);

    QTextTable *table = cursor.insertTable(4, 4, tableFormat);

    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::Bold);

    cursor.setPosition(table->cellAt(0, 0).firstPosition());
    cursor.insertText("Name", headerFormat);

    cursor.setPosition(table->cellAt(0, 1).firstPosition());
    cursor.insertText(info.name);

    cursor.setPosition(table->cellAt(1, 0).firstPosition());
    cursor.insertText("Case ID", headerFormat);

    cursor.setPosition(table->cellAt(1, 1).firstPosition());
    cursor.insertText(info.caseId);

    cursor.setPosition(table->cellAt(1, 2).firstPosition());
    cursor.insertText("Gender", headerFormat);

    cursor.setPosition(table->cellAt(1, 3).firstPosition());
    cursor.insertText(info.gender);

    cursor.setPosition(table->cellAt(2, 0).firstPosition());
    cursor.insertText("MRN/PIN", headerFormat);

    cursor.setPosition(table->cellAt(2, 1).firstPosition());
    cursor.insertText(info.mrn);

    cursor.setPosition(table->cellAt(2, 2).firstPosition());
    cursor.insertText("Date of Birth", headerFormat);

    cursor.setPosition(table->cellAt(2, 3).firstPosition());
    cursor.insertText(info.dateOfBirth);

    cursor.setPosition(table->cellAt(3, 0).firstPosition());
    cursor.insertText("Age", headerFormat);

    cursor.setPosition(table->cellAt(3, 1).firstPosition());
    cursor.insertText(info.age);

    cursor.setPosition(table->cellAt(3, 2).firstPosition());
    cursor.insertText("Exam Date", headerFormat);

    cursor.setPosition(table->cellAt(3, 3).firstPosition());
    cursor.insertText(info.examDate);

    table->mergeCells(0, 1, 1, 3);
}

void Widget::createBiopsyTypeTable(QTextCursor &cursor,
                                   const double &psaValue) {
    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellSpacing(0);

    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 33)
                << QTextLength(QTextLength::PercentageLength, 33)
                << QTextLength(QTextLength::PercentageLength, 34);
    tableFormat.setColumnWidthConstraints(constraints);

    QTextBlockFormat alignCenterFormat;
    alignCenterFormat.setAlignment(Qt::AlignCenter);

    QTextTable *table = cursor.insertTable(2, 3, tableFormat);

    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::Bold);

    cursor.setPosition(table->cellAt(0, 0).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Biopsy Type", headerFormat);

    cursor.setPosition(table->cellAt(0, 1).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Exam Part", headerFormat);

    cursor.setPosition(table->cellAt(0, 2).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("PSA Value", headerFormat);

    cursor.setPosition(table->cellAt(1, 0).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Ultrasound");

    cursor.setPosition(table->cellAt(1, 1).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Prostate");

    cursor.setPosition(table->cellAt(1, 2).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText(QString("%1 ng/mL").arg(psaValue));
}

void Widget::createBiopsyModelTable(QTextCursor &cursor,
                                    const ReportBiopsyModelInfo &info) {
    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellSpacing(0);

    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 33)
                << QTextLength(QTextLength::PercentageLength, 33)
                << QTextLength(QTextLength::PercentageLength, 34);
    tableFormat.setColumnWidthConstraints(constraints);

    QTextTable *table = cursor.insertTable(9, 3, tableFormat);

    std::vector<QString> modelNames;
    modelNames.push_back("Prostate");
    for (int i = 0; i < 7; i++)
        modelNames.push_back(QString("ROI %1").arg(i + 1));

    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::Bold);

    QTextBlockFormat alignCenterFormat;
    alignCenterFormat.setAlignment(Qt::AlignCenter);

    for (int i = 0; i < modelNames.size(); ++i) {
        cursor.setPosition(table->cellAt(i + 1, 0).firstPosition());
        cursor.setBlockFormat(alignCenterFormat);
        cursor.insertText(modelNames[i]);

        cursor.setPosition(table->cellAt(i + 1, 1).firstPosition());
        cursor.setBlockFormat(alignCenterFormat);
        cursor.insertText(info.volumes[i]);

        cursor.setPosition(table->cellAt(i + 1, 2).firstPosition());
        cursor.setBlockFormat(alignCenterFormat);
        cursor.insertText(info.piRads[i]);
    }

    cursor.setPosition(table->cellAt(0, 0).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Model", headerFormat);

    cursor.setPosition(table->cellAt(0, 1).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Volume (cc)", headerFormat);

    cursor.setPosition(table->cellAt(0, 2).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("PI-RADS", headerFormat);
}
