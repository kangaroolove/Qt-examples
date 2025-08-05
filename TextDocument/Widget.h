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
};