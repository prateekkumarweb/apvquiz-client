#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "Player.h"

namespace Ui {
class Mainwindow;
}

class Mainwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Mainwindow(Player usr, QWidget *parent = 0);
    ~Mainwindow();

private slots:
    void on_harryPotterPushButton_clicked();

    void on_gkPushButton_clicked();

    void on_bollywoodPushButton_clicked();

    void on_hollywodPushButton_clicked();

private:
    void updateBoard();

    void hideWidgets();

    void setPics();

private:
    Ui::Mainwindow *ui;
    Player plr;
};

#endif // MAINWINDOW_H
