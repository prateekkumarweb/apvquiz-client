#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timermanage()));
    starttime = new QTime(0,0,20);
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logInPushButton_clicked()
{
    //ui->offlineLabel->setText("There was a connection problem.\n Please check your network.");
    //ui->offlineTextBrowser->setText("There was a connection problem. Please check your network.");
    QString clicktime = ui->label->text();
    timer->stop();
    qDebug() << "Time at which login button clicked " << clicktime;
    ui->logInPushButton->setStyleSheet("background-color: rgb(255,0,0);");

}

void MainWindow::timermanage()
{
    QTime time = QTime::currentTime();
    starttime->setHMS(0,0,starttime->addSecs(-1).second());
    //ui->label->text(starttime->toString());
    QString remainingTime = starttime->toString().right(2);
    ui->label->setText(remainingTime);
    if(remainingTime == "00"){
        timer->stop();
        qDebug() << "Time up ..";
    }
    //qDebug() << "Update ..";
}
