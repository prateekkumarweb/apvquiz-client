#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(Player usr, QString sub, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    //ui->utilityLabel->setText("Looking for opponents."+sub);
    plr = usr;
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}
