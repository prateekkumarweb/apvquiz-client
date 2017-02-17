#include "firstwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    //QString playerName ;//= "Vaibhav";

    QApplication a(argc, argv);
    FirstWindow w;
    w.show();

    return a.exec();
}
