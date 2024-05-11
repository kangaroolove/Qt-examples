#include "Widget.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <qsqlerror.h>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    auto database = QSqlDatabase::addDatabase("QSQLITE", "Data Source=test.db;Version=3;");
    database.setHostName("q3514");
    database.setDatabaseName("test.db");
    database.setUserName("testDB");
    // QSQLITE didn't support password
    database.setPassword("147258");
    if (!database.open())
    {
        qDebug()<<"Cannot open the database";
        qDebug()<<database.lastError().text();
        return;
    }

    QSqlQuery sql(database);   
    qDebug()<<sql.exec("CREATE TABLE Customers (CustomerID INT PRIMARY KEY, FirstName VARCHAR(255) NOT NULL, LastName VARCHAR(255) NOT NULL, Email VARCHAR(255) UNIQUE)");

    QSqlQuery insertSql(database);
    qDebug()<<insertSql.exec("INSERT INTO Customers (CustomerID, FirstName, LastName, Email) VALUES (0, 'a', 'a', '123')" );
}

Widget::~Widget()
{

}