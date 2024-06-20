#pragma once

#include <QWidget>
#include <QSqlDatabase>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
    /**
     * @brief Create the database and this function should be run when there is no database otherwise QSqlQuery will return false
     * 
     * @param database 
     */
    void createDatabase(const QSqlDatabase& database);
    bool isDatabaseCreated();
};