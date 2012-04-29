#include <QtGui/QApplication>
#include "widget.h"


int main(int argc, char *argv[]) //main program
{

    QApplication a(argc, argv); //manages the GUI application's control flow and main settings

    Widget w;   //creates an object of the class defined in "widget.h"

#if defined(Q_WS_S60) // widget display function for Symbian OS
    w.showMaximized();
#else
    w.show(); // widget display function for others including Maemo
#endif

    return a.exec();
}
