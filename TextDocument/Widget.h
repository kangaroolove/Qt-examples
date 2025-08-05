#pragma once

#include <QWidget>

struct ReportHeaderInfo {
    QImage companyLogo;
    QImage hospitalLogo;
    QString hospitalName;
    QString hospitalAddress;
    QString hospitalPhone;
};

class QTextCursor;
class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

private:
    void createReportHeader(QTextCursor& cursor, const ReportHeaderInfo& info);
};