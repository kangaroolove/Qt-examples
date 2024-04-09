#include <QApplication>
#include "ClientWidget.h"
#include <log4qt/logger.h>
#include <log4qt/consoleappender.h>
#include <log4qt/ttcclayout.h>
#include <log4qt/fileappender.h>
#include <log4qt/logmanager.h>
#include <log4qt/loggerrepository.h>
#include <QDateTime>

void initializeRootLogger()
{
    // Create a layout
    auto logger = Log4Qt::Logger::rootLogger();
    auto layout = new Log4Qt::TTCCLayout();
    layout->setName("My Layout");
    layout->setDateFormat("ISO8601");
    // Hide preFixing
    layout->setCategoryPrefixing(false);
    // Hide thread printing
    layout->setThreadPrinting(false);
    layout->activateOptions();
    // Create a console appender
    auto consoleAppender = new Log4Qt::ConsoleAppender(layout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
    consoleAppender->setName("My Appender");
    consoleAppender->activateOptions();
    // Add appender on root logger
    logger->addAppender(consoleAppender);

    // Create a file appender
    auto fileAppender = new Log4Qt::FileAppender(layout, QCoreApplication::applicationDirPath() + "/logs/" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".txt", true);
    fileAppender->setName("My file appender");
    fileAppender->activateOptions();

    logger->addAppender(fileAppender);

    // Set level to info
    logger->setLevel(Log4Qt::Level::INFO_INT);
    Log4Qt::LogManager::setHandleQtMessages(true);
}

void shutDownRootLogger()
{
    auto logger = Log4Qt::Logger::rootLogger();
    logger->removeAllAppenders();
    logger->loggerRepository()->shutdown();
}

int main( int argc, char** argv )
{
  QApplication app( argc, argv );

  initializeRootLogger();

  ClientWidget widget;
  widget.show();

  auto ret = app.exec();
  shutDownRootLogger();
  return ret;
}
