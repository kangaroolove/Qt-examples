#include "Widget.h"

#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QVBoxLayout>
#include <qsqlerror.h>

Widget::Widget(QWidget *parent) : QWidget(parent), m_tableView(new QTableView) {
  initGui();
  auto database = QSqlDatabase::addDatabase("QSQLITE", "my connection");
  database.setDatabaseName("testDatabase.db");
  if (!database.open()) {
    qDebug() << "Cannot open the database";
    qDebug() << database.lastError().text();
    return;
  }

  if (!isDatabaseCreated())
    createDatabase(database);

  showData(database);
}

Widget::~Widget() {}

void Widget::createDatabase(const QSqlDatabase &database) {
  QStringList cmds;
  cmds << "CREATE TABLE Users (UserID INTEGER PRIMARY KEY AUTOINCREMENT, "
          "Username VARCHAR(50) NOT NULL UNIQUE, Email VARCHAR(100) NOT NULL "
          "UNIQUE);";
  cmds << ("INSERT INTO Users (Username, Email) VALUES ('a', 'a@gmail.com');");
  cmds << ("INSERT INTO Users (Username, Email) VALUES ('b', 'b@gmail.com');");
  QSqlQuery sql(database);
  for (auto &cmd : cmds)
    qDebug() << "cmd = " << cmd << ", result = " << sql.exec(cmd);
}

bool Widget::isDatabaseCreated() {
  QFileInfo fileInfo(QApplication::applicationDirPath() + "/testDatabase.db");
  return fileInfo.size() > 0 ? true : false;
}

void Widget::showData(const QSqlDatabase &database) {
  auto model = new QSqlTableModel(this, database);
  model->setTable("Users");
  model->select();
  m_tableView->setModel(model);
}

void Widget::initGui() {
  auto layout = new QVBoxLayout(this);
  layout->addWidget(m_tableView);
}
