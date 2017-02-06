#include "firstwindow.h"
#include "ui_firstwindow.h"
#include <QMessageBox>


FirstWindow::FirstWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstWindow)
{
    ui->setupUi(this);
}

FirstWindow::~FirstWindow()
{
    delete ui;
}

void FirstWindow::on_loginPushButton_clicked()
{
    //Check for internet connectivity ...
    //if( Internet connection avaliable){
        //Connect to server

        QString username = ui->usernameLineEdit->text();
        QString password = ui->passwordLineEdit->text();

        //Package the username and password
        //Send to server
        //Recieve conformation from server
        //if( Valid login password){
            //hide();
            //Some Stuff ...(Launch main program)
        //} else{
        //QMessageBox::Warning(this,"Login Problem","Please check your username and password");
        //}
    //} else{
    //    QMessageBox::warning(this, "Internet Connectivity","Could not connect to network. Please check internet connectivity.");
    //}
}

void FirstWindow::on_signUpPushButton_clicked()
{
   // if( Internet Connection Aavaliable){
        //Connect to server
        //Some stuff ...
        hide();
        sd = new SignUpDialog();
        sd->exec();
    //} else{
        //QMessageBox::warning(this, "Internet Connectivity","Could not connect to network. Please check internet connectivity.");
    //}
}
