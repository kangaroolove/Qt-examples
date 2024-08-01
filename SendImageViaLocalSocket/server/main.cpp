#include <QApplication>
#include "ServerWidget.h"

int main( int argc, char** argv )
{
  QApplication app( argc, argv );
  ServerWidget widget;
  widget.show();

  return app.exec();
}
