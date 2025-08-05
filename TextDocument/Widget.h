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

class QTextCursor;
class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

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
};