#pragma once

#include <QWidget>
#include <QSqlDatabase>

class QTableView;

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
private:
    void initGui();
    /**
     * @brief Create the database and this function should be run when there is no database otherwise QSqlQuery will return false
     * 
     * @param database 
     */
    void createDatabase(const QSqlDatabase& database);
    bool isDatabaseCreated();
    void showData(const QSqlDatabase& database);

    QTableView* m_tableView;
};