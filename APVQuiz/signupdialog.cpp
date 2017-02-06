#include "signupdialog.h"
#include "ui_signupdialog.h"
#include <QMessageBox>
SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

void SignUpDialog::on_pushButton_clicked()
{
    //Check for internet connectivity ...
    //if(Internet Connection Avaliable){
        //Connect to server

        QString username = ui->usernameLineEdit->text();
        QString password = ui->passwordLineEdit->text();
        QString confirmPassword = ui->confirPasswordLineEdit->text();

        if(password == confirmPassword){
            //Package the username and password
            //Send to server
            //hide();
            //Some stuff ... (Launch main program)
        } else{
            QMessageBox::warning(this,"Password Misamtch","The passwords don't match. Please try again");
        }


   //} else{
        //QMessageBox::warning(this, "Internet Connectivity","Could not connect to network. Please check internet connectivity.");
    //}
}
