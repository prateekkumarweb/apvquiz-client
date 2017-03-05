/**
 * @file firstwindow.h
 * @author Vaibhav
 * @date 5 Mar 2017
 * @brief manages the openning first window
 *
 * Header file for the first window.
 */
#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>
#include "signupdialog.h"
#include "mainwindow.h"

namespace Ui {
class FirstWindow;
}

/**
 * @brief Firstwindow class.
 *
 * Manages all activities of first window. Is live whenever first window is open.
 */
class FirstWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for firstwindow
     *
     * Sets up the UI
     */
    explicit FirstWindow( QWidget *parent = 0);
    ~FirstWindow();

private slots:
    /**
     * @brief Slot for login Button clicked
     *
     * Sends the server credentials for verification and
     * raises error or continues to main window depending
     * on server reply.
     */
    void on_loginPushButton_clicked();

    /**
     * @brief Slot for Sign Up Button clicked
     *
     * Exits the current window and opens signup window.
     */
    void on_signUpPushButton_clicked();

private:

    Ui::FirstWindow *ui; //!< Ui for this class
    SignUpDialog *sd; //!< member variable for creating signup dialog
    Mainwindow *mw; //!< member variable for creating mainwindow
};

#endif // FIRSTWINDOW_H
