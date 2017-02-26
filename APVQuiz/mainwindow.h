#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "Player.h"
#include "gamewindow.h"

namespace Ui {
class Mainwindow;
}

class Mainwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Mainwindow(Player usr, QString ip,QWidget *parent = 0);
    ~Mainwindow();

private slots:
    void on_harryPotterPushButton_clicked();

    void on_gkPushButton_clicked();

    void on_bollywoodPushButton_clicked();

    void on_hollywodPushButton_clicked();

    void on_windowLoaded();

private:
    void updateBoard();

    void hideWidgets();

    void setPics();

    void startGame(QString subject);

protected:
      void showEvent(QShowEvent *ev);

signals:
      void window_loaded();

private:
    Ui::Mainwindow *ui;
    Player plr;
    GameWindow *gw;
    QString ipaddress;
};

#endif // MAINWINDOW_H
