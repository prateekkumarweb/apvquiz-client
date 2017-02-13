#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "semaphore.h"

#include <QPixmap>

Mainwindow::Mainwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
    setWindowTitle("Main Window");
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::Window);
    //show();
    //QPixmap harryPotterPic(/home/vaibhav/Projects/apvquiz-client/APVQuiz/images/Harry-Potter-Hat.ico);
    QPixmap harryPotterPic(":/images/images/Harry-Potter-Hat.ico");
    ui->harryPotterPicLabel->setPixmap(harryPotterPic.scaled(128,128,Qt::KeepAspectRatio));
    QPixmap gkPic(":/images/images/gk.png");
    ui->gkPicLabel->setPixmap(gkPic.scaled(128,128,Qt::KeepAspectRatio));
    QPixmap bollywoodPic(":/images/images/bollywood.png");
    ui->bollywoodPicLabel->setPixmap(bollywoodPic.scaled(128,128,Qt::KeepAspectRatio));
    QPixmap hollywoodPic(":/images/images/hollywood.jpg");
    ui->hollywoodPicLabel->setPixmap(hollywoodPic.scaled(128,128,Qt::KeepAspectRatio));
    //Get values from server
    QString name = "Vaibhav";
    //QString welcomeString = "Hi!! "+name;
    ui->welocomeLabel->setText(ui->welocomeLabel->text() + name);
    int games = 12;
    ui->gamesLabel->setText(ui->gamesLabel->text() + QString::number(games));
    int pts = 12;
    ui->pointsLabel->setText(ui->pointsLabel->text() + QString::number(pts));
    int contri = 12;
    ui->contriLabel->setText(ui->contriLabel->text() + QString::number(contri));

}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::on_harryPotterPushButton_clicked()
{

}

void Mainwindow::on_gkPushButton_clicked()
{

}

void Mainwindow::on_bollywoodPushButton_clicked()
{

}


void Mainwindow::on_hollywodPushButton_clicked()
{

}
