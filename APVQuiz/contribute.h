/**
 * @file contribute.h
 * @author Vaibhav
 * @date 6 Mar 2017
 * @brief manages the openning contribute dialog
 *
 * Header file for the contribute dialog.
 */
#ifndef CONTRIBUTE_H
#define CONTRIBUTE_H

#include <QDialog>

#include "Player.h"

namespace Ui {
class Contribute;
}

/**
 * @brief Contribute class.
 *
 * Manages all activities of contribute dialog. Is live whenever contribute dialog is open.
 */
class Contribute : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for firstwindow
     *
     * Sets up the UI and does some initial set up
     */
    explicit Contribute(Player usr, QString ipaddress,QWidget *parent = 0);
    ~Contribute();

private slots:
    /**
     * @brief Slot for Push Button clicked
     *
     * Submits the all the filled data to server
     */
    void on_submitPushButton_clicked();

private:
    Ui::Contribute *ui; //!< Ui for this class
    Player plr; //!< A Player plr
    QString ip; //!< A String for ip
};

#endif // CONTRIBUTE_H
