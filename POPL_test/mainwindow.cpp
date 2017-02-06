#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logInPushButton_clicked()
{
    ui->offlineLabel->setText("There was a connection problem.\n Please check your network.");
    //ui->offlineTextBrowser->setText("There was a connection problem. Please check your network.");
}
