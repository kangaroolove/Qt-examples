#include "Widget.h"

#include <QSqlQuery>
#include <QDebug>
#include <qsqlerror.h>
#include <QApplication>
#include <QDebug>
#include <QFileInfo>

Widget::Widget(QWidget * parent)
    : QWidget(parent)
{
    auto database = QSqlDatabase::addDatabase("QSQLITE", "my connection");
    database.setDatabaseName("testDatabase.db");
    if (!database.open())
    {
        qDebug()<<"Cannot open the database";
        qDebug()<<database.lastError().text();
        return;
    }

    if (!isDatabaseCreated())
        createDatabase(database);
}

Widget::~Widget()
{

}

void Widget::createDatabase(const QSqlDatabase& database)
{
    QStringList cmds;
    cmds<<"CREATE TABLE Users (UserID INTEGER PRIMARY KEY AUTOINCREMENT, Username VARCHAR(50) NOT NULL UNIQUE, Email VARCHAR(100) NOT NULL UNIQUE);";
    cmds<<("INSERT INTO Users (Username, Email) VALUES ('a', 'a@gmail.com');" );
    cmds<<("INSERT INTO Users (Username, Email) VALUES ('b', 'b@gmail.com');");
    QSqlQuery sql(database);  
    for (auto& cmd : cmds)
        qDebug()<<"cmd = "<<cmd<<", result = "<<sql.exec(cmd);
}

bool Widget::isDatabaseCreated()
{
    QFileInfo fileInfo(QApplication::applicationDirPath() + "/testDatabase.db");
    return fileInfo.size() > 0 ? true : false;
}
