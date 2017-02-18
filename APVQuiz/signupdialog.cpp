#include "signupdialog.h"
#include "ui_signupdialog.h"

#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QtNetwork>
SignUpDialog::SignUpDialog( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
    qDebug() << "Printed";
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

void SignUpDialog::on_continuePushButton_clicked()
{

        QString username = ui->usernameLineEdit->text();
        QString password = ui->passwordLineEdit->text();
        QString confirmPassword = ui->confirPasswordLineEdit->text();
        QString ip = ui->ipLineEdit->text();

        if(password == confirmPassword){
            QUrlQuery postData;
            postData.addQueryItem("username", username);
            postData.addQueryItem("password", password);

            //Check for internet connectivity ...
            //if(Internet Connection Avaliable){
                //Connect to server

                QNetworkAccessManager* manager = new QNetworkAccessManager(this);

                QNetworkRequest req;
                req.setUrl(QUrl("http://localhost:8000/signup"));
                req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

                QNetworkReply *reply = manager->post(req,postData.toString(QUrl::FullyEncoded).toUtf8());

                while(!reply->isFinished()){
                qApp->processEvents();
                }

                QByteArray byteReply = reply->readAll();

                QJsonDocument jsonReply = QJsonDocument::fromJson(byteReply);
                QJsonObject replyObject = jsonReply.object();
                QJsonValue statusValue = replyObject["Status"];
                QJsonValue message = replyObject["Message"];

                qDebug() << jsonReply;

                if(statusValue.toBool()){
                    //playerName = username;
                    Player p(username,password);
                    hide();
                    mw = new Mainwindow(p);
                    mw->exec();
                } else {
                    QMessageBox::warning(this,"Sign Up Error",message.toString());
                }

            //} else{
                 //QMessageBox::warning(this, "Internet Connectivity","Could not connect to network. Please check internet connectivity.");
            //}

        } else{
            QMessageBox::warning(this,"Password Misamtch","The passwords don't match. Please try again");
        }

}
