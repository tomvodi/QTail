/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication::setOrganizationName("QTail");
   QApplication::setApplicationName("QTail");

   QApplication a(argc, argv);
   FilAppenderMainWindow w;
   w.show();

   return a.exec();
}
