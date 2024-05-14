#pragma once

#include <QWidget>
#include <QSqlDatabase>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
    void createDatabase(const QSqlDatabase& database);
    void decryptDatabase(const QSqlDatabase& database);
};