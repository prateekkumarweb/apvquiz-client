#include "firstwindow.h"
#include "ui_firstwindow.h"
#include <QMessageBox>

#include <QDebug>
#include <QNetworkAccessManager>
#include <QtNetwork>
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

    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString ip = ui->iplineEdit->text();

    //Check for internet connectivity ...
    //if( Internet connection avaliable){
        //Connect to server
        QUrlQuery postData;
        postData.addQueryItem("username", username);
        postData.addQueryItem("password", password);

        QNetworkAccessManager* manager = new QNetworkAccessManager(this);

        QNetworkRequest req;
        req.setUrl(QUrl("http://localhost:8000/login"));
        req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

        QNetworkReply *reply = manager->post(req,postData.toString(QUrl::FullyEncoded).toUtf8());

        while(!reply->isFinished())
        {
        qApp->processEvents();
        }

        QByteArray byteReply = reply->readAll();

        QJsonDocument jsonReply = QJsonDocument::fromJson(byteReply);
        QJsonObject replyObject = jsonReply.object();
        QJsonValue value = replyObject["Auth"];
        if( value.toBool() ){
            hide();
            mw = new Mainwindow();
            mw->exec();
        } else{
            QMessageBox::warning(this,"Login Problem","Please check your username and password");
        }
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
