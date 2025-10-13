#include "Widget.h"

#include <QAbstractTextDocumentLayout>
#include <QDebug>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QPushButton>
#include <QTextCursor>
#include <QTextEdit>
#include <QTextImageFormat>
#include <QTextLength>
#include <QTextTableCell>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_textEdit(new QTextEdit(this)),
      m_printer(QPrinter::HighResolution) {
    initGui();
    initPrinter();
    prepareReport(m_textEdit->document(), getReportInfo());
}

void Widget::createReportHeader(QTextCursor &cursor,
                                const ReportHeaderInfo &info) {
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 33);
    constraints << QTextLength(QTextLength::PercentageLength, 33);
    constraints << QTextLength(QTextLength::PercentageLength, 34);

    QTextTableFormat tableFormat;
    tableFormat.setColumnWidthConstraints(constraints);
    tableFormat.setBorder(0);
    auto table = cursor.insertTable(1, 3, tableFormat);

    const int logoWidth = 200;
    const int logoHeight = 100;
    if (!info.companyLogo.isNull()) {
        cursor.setPosition(table->cellAt(0, 0).firstPosition());
        cursor.insertImage(info.companyLogo.scaled(logoWidth, logoHeight,
                                                   Qt::KeepAspectRatio));

        QTextBlockFormat companyLogoBlockFormat;
        companyLogoBlockFormat.setAlignment(Qt::AlignLeft);
        cursor.mergeBlockFormat(companyLogoBlockFormat);
    }

    if (!info.hospitalLogo.isNull()) {
        cursor.setPosition(table->cellAt(0, 1).firstPosition());
        cursor.insertImage(info.hospitalLogo.scaled(logoWidth, logoHeight,
                                                    Qt::KeepAspectRatio));

        QTextBlockFormat hospitalLogoBlockFormat;
        hospitalLogoBlockFormat.setAlignment(Qt::AlignCenter);
        cursor.mergeBlockFormat(hospitalLogoBlockFormat);
    }

    cursor.setPosition(table->cellAt(0, 2).firstPosition());

    QTextBlockFormat alignRightFormat;
    alignRightFormat.setAlignment(Qt::AlignRight);
    alignRightFormat.setLeftMargin(50);
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

    cursor.insertHtml("<br>");
    cursor.insertHtml("<br>");

    QTextCharFormat titleCharFormat;
    titleCharFormat.setFontPointSize(14);
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
    textFormat.setFontPointSize(11);
    cursor.insertText(text, textFormat);

    cursor.setPosition(table->cellAt(0, 2).firstPosition());
    cursor.insertFrame(lineFormat);

    moveCursorBehindTable(cursor);
}

void Widget::createPatientInfoTable(QTextCursor &cursor,
                                    const ReportPatientInfo &info) {
    QTextTableFormat tableFormat;
    // tableFormat.setBorder(1);
    // tableFormat.setBorder(2 / 25.4 * 96);
    tableFormat.setCellPadding(5);
    // tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Dotted);

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
    // tableFormat.setCellSpacing(0);

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
    // tableFormat.setBorder(1);
    tableFormat.setCellPadding(5);
    // tableFormat.setCellSpacing(0);

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
    QTextCursor &cursor, const std::vector<ReportTargetCoreInfo> &targetCores) {
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
    QTextCursor &cursor, const std::vector<ReportSystemCoreInfo> &systemCores) {
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
    int horizontalDisplayCount = 0;

    QTextBlockFormat alignCenterBlockFormat;
    alignCenterBlockFormat.setAlignment(Qt::AlignCenter);

    for (const auto &image : images) {
        currentImageShowVertical = image.height() > image.width();
        if (currentImageShowVertical || lastImageShowVertical ||
            horizontalDisplayCount == 2) {
            insertPageBreak(cursor);
            createReportHeader(cursor, headerInfo);
            createTextWithinLine(cursor, "Image Data");
            horizontalDisplayCount = 0;
        }
        int imageWidth = 2200;
        int imageHeight = currentImageShowVertical ? 3200 : 1600;
        if (!lastImageShowVertical && !currentImageShowVertical &&
            horizontalDisplayCount == 1) {
            cursor.insertHtml("<br>");
            cursor.insertHtml("<br>");
            cursor.insertHtml("<br>");
        }
        if (!currentImageShowVertical) ++horizontalDisplayCount;
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

void Widget::insertPageBreak(QTextCursor &cursor) {
    QTextBlockFormat pageBreakFormat;
    pageBreakFormat.setPageBreakPolicy(
        QTextBlockFormat::PageBreak_AlwaysBefore);
    cursor.insertBlock(pageBreakFormat);
}

void Widget::preparePrint(QTextDocument *document) {
    if (!document) return;

    document->clear();
}

void Widget::prepareReport(QTextDocument *document,
                           const ReportInfo &reportInfo) {
    if (!document) return;
    document->setDocumentMargin(20);
    QFont font;
    font.setPointSize(9);
    document->setDefaultFont(font);

    QTextCursor cursor(document);

    createReportHeader(cursor, reportInfo.headerInfo);
    createTextWithinLine(cursor, "Patient Information");

    createPatientInfoTable(cursor, reportInfo.patientInfo);
    createTextWithinLine(cursor, "MRI information");
    createBiopsyTypeTable(cursor, 4.5);

    cursor.insertHtml("<br>");

    createBiopsyModelTable(cursor, reportInfo.biopsyModelInfo);

    cursor.insertHtml("<br>");
    cursor.insertHtml("<br>");

    QTextCharFormat remarkTextFormat;
    remarkTextFormat.setFontWeight(QFont::Bold);
    remarkTextFormat.setFontPointSize(11);

    cursor.insertText("Remarks:", remarkTextFormat);

    cursor.insertHtml("<br>");

    QTextFrameFormat frameFormat;
    // frameFormat.setBorder(1 / 25.4 * 96);
    frameFormat.setBorder(2);
    frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    // frameFormat.setPadding(10 / 25.4 * 96);
    // frameFormat.setPadding(0);
    frameFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    cursor.insertFrame(frameFormat);
    cursor.insertText(reportInfo.remark);

    auto frame = cursor.currentFrame();
    if (frame) {
        cursor.setPosition(frame->lastPosition() + 1);
    }

    insertPageBreak(cursor);

    createReportHeader(cursor, reportInfo.headerInfo);
    createTextWithinLine(cursor, "Biopsy Summary");

    createBiopsySummaryTable(cursor, reportInfo.biopsySummaryInfo);
    cursor.insertHtml("<br>");

    createTargetCoreTable(cursor, reportInfo.targetCoreInfo);

    cursor.insertHtml("<br>");

    createSystemCoreTable(cursor, reportInfo.systemCoreInfo);

    // HHHV OK
    // HVHH OK
    // VHHH OK
    // HHVH
    // H OK
    // V OK
    createImageGallery(cursor, reportInfo.images, reportInfo.headerInfo);
}

ReportInfo Widget::getReportInfo() {
    ReportInfo reportInfo;

    ReportHeaderInfo headerInfo;
    headerInfo.companyLogo = QImage(":/icons/compangLogo.png");
    headerInfo.hospitalLogo = QImage(":/icons/hispitalLogo.png");
    headerInfo.hospitalName = "abc";
    headerInfo.hospitalAddress =
        "New YorkNew YorkNew YorkNew YorkNew YorkNew YorkNew YorkNew YorkNew "
        "YorkNew YorkNew YorkNew YorkNew YorkNew YorkNew YorkNew YorkNew "
        "YorkNew YorkNew YorkNew YorkNew YorkNew YorkNew YorkNew YorkNew "
        "YorkNew YorkNew YorkNew YorkNew YorkNew YorkNew York";
    headerInfo.hospitalPhone = "123456";
    reportInfo.headerInfo = headerInfo;

    ReportPatientInfo patientInfo;
    patientInfo.name = "Erick Lee";
    patientInfo.caseId = "25";
    patientInfo.gender = "Male";
    patientInfo.mrn = "J1122334K";
    patientInfo.dateOfBirth = "1971-06-03";
    patientInfo.age = "54";
    patientInfo.examDate = "2025-06-30";
    reportInfo.patientInfo = patientInfo;

    ReportBiopsyModelInfo modelInfo;
    modelInfo.piRads = {"5", "2", "3", "1", "5", "4", "3", "2"};
    modelInfo.volumes = {"5", "2", "3", "1", "5", "10", "3", "2"};
    reportInfo.biopsyModelInfo = modelInfo;

    reportInfo.remark =
        "Hello world!\nHello world!\nHello world!\nHello world!\nHello "
        "world!\nHello world!\nHello world!\nHello world!\nHello world!\nHello "
        "world!\nHello world!\nHello world!\nHello world!\nHello world!\nHello "
        "world!\nHello world!\nHello world!\nHello world!\nHello world!\nHello "
        "world!\nHello world!\nHello world!\nHello world!\nHello world!\nHello "
        "world!\nHello world!\nHello world!\nHello world!\nHello world!\nHello "
        "world!\nHello world!\nHello world!\nHello world!\nHello world!\nHello "
        "world!\n";

    ReportBiopsySummaryInfo biopsySummaryInfo;
    biopsySummaryInfo.doneTargetCores = "15";
    biopsySummaryInfo.skippedTargetCores = "1";
    biopsySummaryInfo.doneSystemCores = "24";
    biopsySummaryInfo.skippedSystemCores = "3";
    biopsySummaryInfo.totalDoneCores = "39";
    biopsySummaryInfo.totalSkippedCores = "4";
    reportInfo.biopsySummaryInfo = biopsySummaryInfo;

    std::vector<ReportTargetCoreInfo> targetCores = {
        {"T1", "ROI 1", "Done"}, {"T2", "ROI 2", "Skipped"}};
    reportInfo.targetCoreInfo = targetCores;

    std::vector<ReportSystemCoreInfo> systemCores = {
        {"S1", "Right Anterior", "Done"}, {"S2", "Right Posterior", "Skipped"}};
    reportInfo.systemCoreInfo = systemCores;

    std::vector<QImage> images = {
        // QImage(":icons/1.jpg"), QImage(":icons/2.jpg"),
        // QImage(":icons/3.jpg"),
        // QImage(":icons/4.jpg"), QImage(":icons/5.jpg"),
    };
    reportInfo.images = images;

    return reportInfo;
}

QTextDocument *Widget::document() const { return m_textEdit->document(); }

void Widget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    static bool firstTime = true;
    if (firstTime) {
        auto doc = m_textEdit->document();
        firstTime = false;
        const double pageWidth = 793;
        const double pageHeight = 1123;
        doc->setPageSize(QSize(pageWidth, pageHeight));
    }
}

void Widget::initGui() {
    auto layout = new QVBoxLayout(this);
    m_textEdit->setReadOnly(true);
    layout->addWidget(m_textEdit);

    auto button = new QPushButton("Print", this);
    layout->addWidget(button);

    m_font.setPointSize(9);

    connect(button, &QPushButton::clicked, this, [this] {
        auto doc = m_textEdit->document()->clone();

        auto rootFrame = doc->rootFrame();
        auto it = rootFrame->begin();
        while (!it.atEnd()) {
            auto frame = it.currentFrame();
            if (frame) {
                auto format = frame->frameFormat();
                if (format.borderStyle() ==
                    QTextFrameFormat::BorderStyle_Solid) {
                    qDebug() << "border = " << format.border();
                    qDebug() << "padding = " << format.padding();

                    auto border = format.border();
                    format.setBorder(2.0 * border / 25.4 * 96.0);

                    auto padding = format.padding();
                    format.setPadding(2.0 * padding / 25.4 * 96.0);
                    frame->setFrameFormat(format);
                    break;
                }
            }
            ++it;
        }

        const int horizontalMargin = int((0 / 2.54) * 96);
        const int verticalMargin = int((10 / 25.4) * 96);
        QTextFrameFormat fmt = doc->rootFrame()->frameFormat();
        fmt.setLeftMargin(0);
        fmt.setRightMargin(0);
        fmt.setTopMargin(int((10 / 25.4) * 96));
        fmt.setBottomMargin(int((80 / 25.4) * 96));
        doc->rootFrame()->setFrameFormat(fmt);
#if 1
        const double dpi = 96.0;
        const double inch = 25.4;
        double pageMargin = 20 / dpi * inch;

        QPrinter printer(QPrinter::HighResolution);
        printer.setOrientation(QPrinter::Portrait);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("D:/test.pdf");
        printer.setMargins({pageMargin, pageMargin, pageMargin, pageMargin});

        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing);
        auto body = QRectF(0, 0, printer.width(), printer.height() - 10);

        doc->documentLayout()->setPaintDevice(&printer);
        doc->setPageSize(printer.pageRect().size());
        auto count = doc->pageCount();

        for (int index = 1; index <= count; ++index) {
            painter.save();
            painter.translate(body.left(),
                              body.top() - (index - 1) * body.height());
            QRectF view(0, (index - 1) * body.height(), body.width(),
                        body.height());

            QAbstractTextDocumentLayout::PaintContext ctx;
            painter.setClipRect(view);
            ctx.clip = view;
            ctx.palette.setColor(QPalette::Text, Qt::black);

            auto layout = doc->documentLayout();
            layout->draw(&painter, ctx);

            QFont textfont;
            textfont.setPointSize(m_font.pointSize());
            textfont.setBold(true);
            QFontMetrics fm(m_font, &printer);
            QRect footerRect(body.left(), body.bottom() * index - fm.height(),
                             body.width(), fm.height());

            painter.setFont(textfont);
            painter.drawText(footerRect, Qt::AlignLeft | Qt::AlignVCenter,
                             QString("Patient Name: %1").arg("Error"));
            painter.drawText(footerRect, Qt::AlignRight | Qt::AlignVCenter,
                             QString("Page %1 of %2").arg(index).arg(count));

            painter.restore();
            if (index != count) printer.newPage();
        }

        // End painting
        painter.end();
#endif

        qDebug() << "size = " << doc->pageSize();
        qDebug() << "count=" << doc->pageCount();
    });
}

void Widget::initPrinter() {
    m_printer.setOrientation(QPrinter::Portrait);
    m_printer.setPaperSize(QPrinter::A4);
    m_printer.setOutputFormat(QPrinter::PdfFormat);
    m_printer.setOutputFileName("D:/test.pdf");
    // m_printer.setResolution(300);
    m_printer.setMargins({0, 0, 0, 0});
}
