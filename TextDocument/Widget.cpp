#include "Widget.h"

#include <QDebug>
#include <QPrintDialog>
#include <QPrinter>
#include <QPushButton>
#include <QTextCursor>
#include <QTextEdit>
#include <QTextImageFormat>
#include <QTextLength>
#include <QTextTableCell>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    auto layout = new QVBoxLayout(this);
    auto textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    layout->addWidget(textEdit);

    auto document = textEdit->document();

    auto button = new QPushButton("Print", this);
    connect(button, &QPushButton::clicked, this, [=] {
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOrientation(QPrinter::Portrait);
        printer.setPaperSize(QPrinter::A4);

        QPrintDialog dialog(&printer);
        if (dialog.exec() == QDialog::Accepted) {
            document->print(&printer);
        }
    });
    layout->addWidget(button);

    QTextCursor cursor(document);

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

    ReportPatientInfo patientInfo;
    patientInfo.name = "Erick Lee";
    patientInfo.caseId = "25";
    patientInfo.gender = "Male";
    patientInfo.mrn = "J1122334K";
    patientInfo.dateOfBirth = "1971-06-03";
    patientInfo.age = "54";
    patientInfo.examDate = "2025-06-30";
    createPatientInfoTable(cursor, patientInfo);
    createTextWithinLine(cursor, "MRI information");
    createBiopsyTypeTable(cursor, 4.5);

    cursor.insertHtml("<br>");

    ReportBiopsyModelInfo modelInfo;
    modelInfo.piRads = {"5", "2", "3", "1", "5", "4", "3", "2"};
    modelInfo.volumes = {"5", "2", "3", "1", "5", "10", "3", "2"};
    createBiopsyModelTable(cursor, modelInfo);
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

    auto frame = cursor.currentFrame();
    if (frame) {
        cursor.setPosition(frame->lastPosition() + 1);
    }

    createReportHeader(cursor, headerInfo);
    createTextWithinLine(cursor, "Biopsy Summary");

    ReportBiopsySummaryInfo biopsySummaryInfo;
    biopsySummaryInfo.doneTargetCores = "15";
    biopsySummaryInfo.skippedTargetCores = "1";
    biopsySummaryInfo.doneSystemCores = "24";
    biopsySummaryInfo.skippedSystemCores = "3";
    biopsySummaryInfo.totalDoneCores = "39";
    biopsySummaryInfo.totalSkippedCores = "4";
    createBiopsySummaryTable(cursor, biopsySummaryInfo);
    cursor.insertHtml("<br>");

    std::vector<TargetCoreInfo> targetCores = {{"T1", "ROI 1", "Done"},
                                               {"T2", "ROI 2", "Skipped"}};
    createTargetCoreTable(cursor, targetCores);

    cursor.insertHtml("<br>");

    std::vector<SystemCoreInfo> systemCores = {
        {"S1", "Right Anterior", "Done"}, {"S2", "Right Posterior", "Skipped"}};
    createSystemCoreTable(cursor, systemCores);

    // HHHV OK
    // HVHH OK
    // VVHHH OK
    // VHHH
    // H OK
    // V OK
    std::vector<QImage> images = {
        QImage("C:/Users/q3514/Desktop/HTML/v.png"),
        QImage("C:/Users/q3514/Desktop/HTML/h.png"),
        QImage("C:/Users/q3514/Desktop/HTML/h.png"),
        QImage("C:/Users/q3514/Desktop/HTML/h.png"),
    };
    createImageGallery(cursor, images, headerInfo);
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
    if (!info.companyLogo.isNull()) {
        cursor.setPosition(table->cellAt(0, 0).firstPosition());
        cursor.insertImage(
            info.companyLogo.scaled(logoSize, logoSize, Qt::KeepAspectRatio));

        QTextBlockFormat companyLogoBlockFormat;
        companyLogoBlockFormat.setAlignment(Qt::AlignLeft);
        cursor.mergeBlockFormat(companyLogoBlockFormat);
    }

    if (!info.hospitalLogo.isNull()) {
        cursor.setPosition(table->cellAt(0, 1).firstPosition());
        cursor.insertImage(
            info.hospitalLogo.scaled(logoSize, logoSize, Qt::KeepAspectRatio));

        QTextBlockFormat hospitalLogoBlockFormat;
        hospitalLogoBlockFormat.setAlignment(Qt::AlignCenter);
        cursor.mergeBlockFormat(hospitalLogoBlockFormat);
    }

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

    moveCursorBehindTable(cursor);

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

    moveCursorBehindTable(cursor);
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

    moveCursorBehindTable(cursor);
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

    moveCursorBehindTable(cursor);
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

    moveCursorBehindTable(cursor);
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

    moveCursorBehindTable(cursor);
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

    moveCursorBehindTable(cursor);
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

    moveCursorBehindTable(cursor);
}

void Widget::createImageGallery(QTextCursor &cursor,
                                const std::vector<QImage> &images,
                                const ReportHeaderInfo &headerInfo) {
    if (images.empty()) return;

    bool lastImageShowVertical = true;
    bool currentImageShowVertical = false;
    bool newPage = false;

    QTextBlockFormat alignCenterBlockFormat;
    alignCenterBlockFormat.setAlignment(Qt::AlignCenter);

    for (const auto &image : images) {
        currentImageShowVertical = image.height() > image.width();
        if (newPage || currentImageShowVertical || lastImageShowVertical) {
            createReportHeader(cursor, headerInfo);
            createTextWithinLine(cursor, "Image Data");
            newPage = false;
        }
        int imageWidth = currentImageShowVertical ? 1080 : 1920;
        int imageHeight = currentImageShowVertical ? 1920 : 1080;
        if (!lastImageShowVertical && !currentImageShowVertical) {
            cursor.insertHtml("<br>");
            cursor.insertHtml("<br>");
            cursor.insertHtml("<br>");
            newPage = true;
        }
        cursor.insertImage(
            image.scaled(imageWidth, imageHeight, Qt::KeepAspectRatio));
        cursor.mergeBlockFormat(alignCenterBlockFormat);
        lastImageShowVertical = currentImageShowVertical;
    }
}

void Widget::moveCursorBehindTable(QTextCursor &cursor) {
    auto table = cursor.currentTable();
    if (table) {
        int endOfTablePos = table->lastPosition() + 1;
        cursor.setPosition(endOfTablePos);
    }
}
