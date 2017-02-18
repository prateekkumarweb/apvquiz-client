#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include "Player.h"
namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(Player usr, QString sub, QWidget *parent = 0);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    Player plr;
    QString subject;
};

#endif // GAMEWINDOW_H
