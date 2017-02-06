#include "firstwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FirstWindow w;
    w.show();

    return a.exec();
}
