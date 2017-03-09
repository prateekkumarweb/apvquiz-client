/**
 * @file mainwindow.h
 * @author Vaibhav
 * @date 5 Mar 2017
 * @brief manages the openning main window
 *
 * Header file for the main window.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "Player.h"
#include "gamewindow.h"
#include "contribute.h"

namespace Ui {
class Mainwindow;
}

/**
 * @brief Mainwindow class.
 *
 * Manages all activities of main window. Is live whenever main window is open.
 */
class Mainwindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for mainwindow
     *
     * Sets up the UI, converts to window from dialog
     * and initializes member varibles formm the passed arguments
     */
    explicit Mainwindow(Player usr, QString ip,QWidget *parent = 0);

    /**
     * @brief Destructor for mainwindow
     *
     * Deletes the UI
     */
    ~Mainwindow();


    /* Documentation for each of the function can be obtained in the
     * corresponding mainwindow.cpp. The header contains all declaration.
     */

private slots:
    void on_harryPotterPushButton_clicked();

    void on_gkPushButton_clicked();

    void on_windowLoaded();

    void on_animePushButton_clicked();

    void on_moviesPushButton_clicked();

    void on_computersPushButton_clicked();

    void on_sciencePushButton_clicked();

    void on_gotPushButton_clicked();

    void on_tiviaPushButton_clicked();

    void on_sportsPushButton_clicked();

    void on_contributePushButton_clicked();

private:
    void updateBoard();

    void setPics();

    void startGame(QString subject);

protected:
      void showEvent(QShowEvent *ev);

signals:
      void window_loaded();

private:
    Ui::Mainwindow *ui; //!< Ui for this class
    Player plr; //!< A Player plr
    GameWindow *gw; //!< member variable for creating game window
    Contribute *cw; //!< member variable for creating contribution window
    QString ipaddress; //!< String for ipAddress
};

#endif // MAINWINDOW_H
