/**
 * @file main.cpp
 * @author Vaibhav
 * @date 5 Mar 2017
 * @brief Contains main()
 */
#include "firstwindow.h"
#include <QApplication>


/**
 * @brief Main function
 *
 * Main function of the entire project
 */
int main(int argc, char *argv[])
{
    /* Create an application */
    QApplication a(argc, argv);

    /* Create an object of first window, set its size and then show it */
    FirstWindow w;
    w.setFixedSize(949,677);
    w.show();

    /* Execute the application */
    return a.exec();
}
