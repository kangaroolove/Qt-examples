#include <QApplication>
#include "DaqcServer.h"

int main( int argc, char** argv )
{
  QApplication app( argc, argv );
  DaqcServer server;
  server.start();

  return app.exec();
}
