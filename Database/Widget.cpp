#include "Widget.h"

#include <QSqlQuery>
#include <QDebug>
#include <qsqlerror.h>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    auto database = QSqlDatabase::addDatabase("QSQLCIPHER", "my connection");
    database.setDatabaseName("test3.db");
    if (!database.open())
    {
        qDebug()<<"Cannot open the database";
        qDebug()<<database.lastError().text();
        return;
    }

    createDatabase(database);
}

Widget::~Widget()
{

}

void Widget::createDatabase(const QSqlDatabase& database)
{
    //QSqlQuery encrypSql(database);
    //encrypSql.exec("PRAGMA key='!@123Da'");

    // QSqlQuery sql(database);   
    // qDebug()<<sql.exec("CREATE TABLE Customers (CustomerID INT PRIMARY KEY, FirstName VARCHAR(255) NOT NULL, LastName VARCHAR(255) NOT NULL, Email VARCHAR(255) UNIQUE)");

    // QSqlQuery insertSql(database);
    // qDebug()<<insertSql.exec("INSERT INTO Customers (CustomerID, FirstName, LastName, Email) VALUES (0, 'a', 'a', '123')" );

    QString cmd;
    cmd.append("CREATE TABLE Customers (CustomerID INT PRIMARY KEY, FirstName VARCHAR(255) NOT NULL, LastName VARCHAR(255) NOT NULL, Email VARCHAR(255) UNIQUE);");
    cmd.append("INSERT INTO Customers (CustomerID, FirstName, LastName, Email) VALUES (0, 'a', 'a', '123');" );
    QSqlQuery sql(database);  
    qDebug()<<sql.exec(cmd);
}

void Widget::decryptDatabase(const QSqlDatabase& database)
{
    QSqlQuery encrypSql(database);
    qDebug()<<encrypSql.exec("PRAGMA key='!@123Da'");

    QSqlQuery attachSql(database);
    qDebug()<<attachSql.exec("ATTACH DATABASE 'plaintext.db' AS plaintext KEY '';");

    QSqlQuery exportDatabaseSql(database);
    qDebug()<<exportDatabaseSql.exec("SELECT sqlcipher_export('plaintext');");

    QSqlQuery detachSql(database);
    qDebug()<<detachSql.exec("DETACH DATABASE plaintext");
}
