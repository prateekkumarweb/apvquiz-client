#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "Player.h"
#include "gamewindow.h"
#include "contribute.h"

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
    Contribute *cw;
    QString ipaddress;
};

#endif // MAINWINDOW_H
