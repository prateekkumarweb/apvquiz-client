/**
 * @file main.cpp
 * @author Vaibhav
 * @date 5 Mar 2017
 * @brief Contains main()
 */
#include "firstwindow.h"
#include <QApplication>


/**
 * @brief main function
 *
 * Main function of the entire project
 */
int main(int argc, char *argv[])
{
    /* Create an application */
    QApplication a(argc, argv);

    /* Create an object of first window and then show it */
    FirstWindow w;
    //w.setWindowFlags( Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::CustomizeWindowHint);
    w.show();

    /* Execute the application */
    return a.exec();
}
