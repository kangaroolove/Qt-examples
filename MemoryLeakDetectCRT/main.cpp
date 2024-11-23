#include "Widget.h"
#include <QApplication>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>

#ifdef _DEBUG
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

int main(int argc, char *argv[]) {
  // Multiple exits
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  QApplication a(argc, argv);
  Widget widget;
  widget.show();

  _CrtDumpMemoryLeaks();
  return a.exec();
}
