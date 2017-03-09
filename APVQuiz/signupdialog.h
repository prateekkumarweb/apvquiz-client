/**
 * @file signupdialog.h
 * @author Vaibhav
 * @date 5 Mar 2017
 * @brief manages the openning first window
 *
 * Header file for the first window.
 */
#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class SignUpDialog;
}

/**
 * @brief SignUpDialog class.
 *
 * Manages all activities of sign up dialog. Is live whenever sign up dialog is open.
 */
class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for sign up dialog
     *
     * Sets up the UI
     */
    explicit SignUpDialog(QWidget *parent = 0);

    /**
     * @brief Destructor for signup dialog
     *
     * Deletes the UI
     */
    ~SignUpDialog();

private slots:
    /**
     * @brief Slot for continue Button clicked
     *
     * Sends the server credentials for the new
     * user. Based on the reply of the user raises
     * error or continues to main window
     */
    void on_continuePushButton_clicked();

private:
    Ui::SignUpDialog *ui; //!< Ui for this class
    Mainwindow *mw; //!< member variable for creating mainwindow
};

#endif // SIGNUPDIALOG_H
