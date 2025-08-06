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
    cursor.insertHtml("<br>");

    ReportBiopsyModelInfo modelInfo;
    modelInfo.piRads = {"5", "2", "3", "1", "5", "4", "3", "2"};
    modelInfo.volumes = {"5", "2", "3", "1", "5", "10", "3", "2"};
    createBiopsyModelTable(cursor, modelInfo);
    cursor.setPosition(frame->lastPosition());
    cursor.insertHtml("<br>");

    cursor.insertHtml("<br>");

    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    cursor.setCharFormat(boldFormat);
    cursor.insertText("Remarks:");

    cursor.insertHtml("<br>");

    QTextFrameFormat frameFormat;
    frameFormat.setBorder(1);
    frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    frameFormat.setPadding(0);
    frameFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    frameFormat.setHeight(100);
    cursor.insertFrame(frameFormat);

    cursor.setPosition(frame->lastPosition());

    createReportHeader(cursor, headerInfo);
    createTextWithinLine(cursor, "Biopsy Summary");

    cursor.setPosition(frame->lastPosition());

    ReportBiopsySummaryInfo biopsySummaryInfo;
    biopsySummaryInfo.doneTargetCores = "15";
    biopsySummaryInfo.skippedTargetCores = "1";
    biopsySummaryInfo.doneSystemCores = "24";
    biopsySummaryInfo.skippedSystemCores = "3";
    biopsySummaryInfo.totalDoneCores = "39";
    biopsySummaryInfo.totalSkippedCores = "4";
    createBiopsySummaryTable(cursor, biopsySummaryInfo);
    cursor.setPosition(frame->lastPosition());
    cursor.insertHtml("<br>");

    std::vector<TargetCoreInfo> targetCores = {{"T1", "ROI 1", "Done"},
                                               {"T2", "ROI 2", "Skipped"}};
    createTargetCoreTable(cursor, targetCores);

    cursor.setPosition(frame->lastPosition());
    cursor.insertHtml("<br>");

    std::vector<SystemCoreInfo> systemCores = {
        {"S1", "Right Anterior", "Done"}, {"S2", "Right Posterior", "Skipped"}};
    createSystemCoreTable(cursor, systemCores);

    cursor.setPosition(frame->lastPosition());

    createReportHeader(cursor, headerInfo);
    createTextWithinLine(cursor, "Image Data");

#if 0


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
    tableFormat.setCellPadding(5);
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
    tableFormat.setCellPadding(5);
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

    cursor.setPosition(table->cellAt(0, 0).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Model", headerFormat);

    cursor.setPosition(table->cellAt(0, 1).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Volume (cc)", headerFormat);

    cursor.setPosition(table->cellAt(0, 2).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("PI-RADS", headerFormat);

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
}

void Widget::createBiopsySummaryTable(QTextCursor &cursor,
                                      const ReportBiopsySummaryInfo &info) {
    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellPadding(5);
    tableFormat.setCellSpacing(0);

    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 29)
                << QTextLength(QTextLength::PercentageLength, 29);
    tableFormat.setColumnWidthConstraints(constraints);

    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::Bold);

    QTextBlockFormat alignCenterFormat;
    alignCenterFormat.setAlignment(Qt::AlignCenter);

    QTextTable *table = cursor.insertTable(3, 5, tableFormat);

    cursor.setPosition(table->cellAt(0, 1).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Target cores", headerFormat);

    cursor.setPosition(table->cellAt(0, 2).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("System cores", headerFormat);

    cursor.setPosition(table->cellAt(0, 3).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Total cores done", headerFormat);

    cursor.setPosition(table->cellAt(0, 4).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Total cores skipped", headerFormat);

    cursor.setPosition(table->cellAt(1, 0).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Done");

    cursor.setPosition(table->cellAt(1, 1).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText(info.doneTargetCores);

    cursor.setPosition(table->cellAt(1, 2).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText(info.doneSystemCores);

    cursor.setPosition(table->cellAt(1, 3).firstPosition());
    auto totalDoneCores = table->cellAt(1, 3).format();
    totalDoneCores.setVerticalAlignment(QTextCharFormat::AlignMiddle);
    table->cellAt(1, 3).setFormat(totalDoneCores);
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText(info.totalDoneCores);

    cursor.setPosition(table->cellAt(1, 4).firstPosition());
    auto totalSkippedCores = table->cellAt(1, 4).format();
    totalSkippedCores.setVerticalAlignment(QTextCharFormat::AlignMiddle);
    table->cellAt(1, 4).setFormat(totalSkippedCores);
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText(info.totalSkippedCores);

    cursor.setPosition(table->cellAt(2, 0).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Skipped");

    cursor.setPosition(table->cellAt(2, 1).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText(info.skippedTargetCores);

    cursor.setPosition(table->cellAt(2, 2).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText(info.skippedSystemCores);

    table->mergeCells(1, 3, 2, 1);
    table->mergeCells(1, 4, 2, 1);
}

void Widget::createTargetCoreTable(
    QTextCursor &cursor, const std::vector<TargetCoreInfo> &targetCores) {
    if (targetCores.empty()) return;

    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellPadding(5);
    tableFormat.setCellSpacing(0);

    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 33)
                << QTextLength(QTextLength::PercentageLength, 33)
                << QTextLength(QTextLength::PercentageLength, 34);
    tableFormat.setColumnWidthConstraints(constraints);

    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::Bold);

    QTextBlockFormat alignCenterFormat;
    alignCenterFormat.setAlignment(Qt::AlignCenter);

    QTextTable *table =
        cursor.insertTable(targetCores.size() + 1, 3, tableFormat);

    cursor.setPosition(table->cellAt(0, 0).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Target Core", headerFormat);

    cursor.setPosition(table->cellAt(0, 1).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Lesion", headerFormat);

    cursor.setPosition(table->cellAt(0, 2).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Status", headerFormat);

    int index = 1;
    for (const auto &core : targetCores) {
        cursor.setPosition(table->cellAt(index, 0).firstPosition());
        cursor.setBlockFormat(alignCenterFormat);
        cursor.insertText(core.name);

        cursor.setPosition(table->cellAt(index, 1).firstPosition());
        cursor.setBlockFormat(alignCenterFormat);
        cursor.insertText(core.lesion);

        cursor.setPosition(table->cellAt(index, 2).firstPosition());
        cursor.setBlockFormat(alignCenterFormat);
        cursor.insertText(core.status);

        ++index;
    }
}

void Widget::createSystemCoreTable(
    QTextCursor &cursor, const std::vector<SystemCoreInfo> &systemCores) {
    if (systemCores.empty()) return;

    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellPadding(5);
    tableFormat.setCellSpacing(0);

    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 33)
                << QTextLength(QTextLength::PercentageLength, 33)
                << QTextLength(QTextLength::PercentageLength, 34);
    tableFormat.setColumnWidthConstraints(constraints);

    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::Bold);

    QTextBlockFormat alignCenterFormat;
    alignCenterFormat.setAlignment(Qt::AlignCenter);

    QTextTable *table =
        cursor.insertTable(systemCores.size() + 1, 3, tableFormat);

    cursor.setPosition(table->cellAt(0, 0).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("System Core", headerFormat);

    cursor.setPosition(table->cellAt(0, 1).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Zone", headerFormat);

    cursor.setPosition(table->cellAt(0, 2).firstPosition());
    cursor.setBlockFormat(alignCenterFormat);
    cursor.insertText("Status", headerFormat);

    int index = 1;
    for (const auto &core : systemCores) {
        cursor.setPosition(table->cellAt(index, 0).firstPosition());
        cursor.setBlockFormat(alignCenterFormat);
        cursor.insertText(core.name);

        cursor.setPosition(table->cellAt(index, 1).firstPosition());
        cursor.setBlockFormat(alignCenterFormat);
        cursor.insertText(core.zone);

        cursor.setPosition(table->cellAt(index, 2).firstPosition());
        cursor.setBlockFormat(alignCenterFormat);
        cursor.insertText(core.status);

        ++index;
    }
}
