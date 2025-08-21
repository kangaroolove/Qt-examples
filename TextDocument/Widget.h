#pragma once

#include <QWidget>

struct ReportHeaderInfo {
    QImage companyLogo;
    QImage hospitalLogo;
    QString hospitalName;
    QString hospitalAddress;
    QString hospitalPhone;
};

struct ReportPatientInfo {
    QString name;
    QString caseId;
    QString gender;
    QString mrn;
    QString dateOfBirth;
    QString age;
    QString examDate;
};

struct ReportBiopsyModelInfo {
    std::vector<QString> volumes;
    std::vector<QString> piRads;
};

struct ReportBiopsySummaryInfo {
    QString doneTargetCores;
    QString skippedTargetCores;
    QString doneSystemCores;
    QString skippedSystemCores;
    QString totalDoneCores;
    QString totalSkippedCores;
};

struct ReportTargetCoreInfo {
    QString name;
    QString lesion;
    QString status;
};

struct ReportSystemCoreInfo {
    QString name;
    QString zone;
    QString status;
};

struct ReportInfo {
    ReportHeaderInfo headerInfo;
    ReportPatientInfo patientInfo;
    ReportBiopsyModelInfo biopsyModelInfo;
    ReportBiopsySummaryInfo biopsySummaryInfo;
    std::vector<ReportTargetCoreInfo> targetCoreInfo;
    std::vector<ReportSystemCoreInfo> systemCoreInfo;
    std::vector<QImage> images;
    QString remark;
};

class QTextCursor;
class QTextDocument;
class QTextEdit;
class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    Widget(QTextDocument& document, QWidget* parent = nullptr);

    void prepareReport(QTextDocument* document, const ReportInfo& reportInfo);
    ReportInfo getReportInfo();
    QTextDocument* document() const;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void createReportHeader(QTextCursor& cursor, const ReportHeaderInfo& info);
    void createTextWithinLine(QTextCursor& cursor, const QString& text);
    void createPatientInfoTable(QTextCursor& cursor,
                                const ReportPatientInfo& info);
    void createBiopsyTypeTable(QTextCursor& cursor, const double& psaValue);
    void createBiopsyModelTable(QTextCursor& cursor,
                                const ReportBiopsyModelInfo& info);
    void createBiopsySummaryTable(QTextCursor& cursor,
                                  const ReportBiopsySummaryInfo& info);
    void createTargetCoreTable(
        QTextCursor& cursor,
        const std::vector<ReportTargetCoreInfo>& targetCores);
    void createSystemCoreTable(
        QTextCursor& cursor,
        const std::vector<ReportSystemCoreInfo>& systemCores);
    void createImageGallery(QTextCursor& cursor,
                            const std::vector<QImage>& images,
                            const ReportHeaderInfo& headerInfo);
    void moveCursorBehindTable(QTextCursor& cursor);
    void insertPageBreak(QTextCursor& cursor);
    void preparePrint(QTextDocument* document);

    void initGui();

    QTextEdit* m_textEdit;
};