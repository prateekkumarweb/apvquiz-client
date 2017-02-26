#include "firstwindow.h"
#include "ui_firstwindow.h"
#include <QMessageBox>

#include <QDebug>
#include <QNetworkAccessManager>
#include <QtNetwork>
FirstWindow::FirstWindow( QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstWindow)
{
   // playerName = name;
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
    QString ipServer = "http://"+ip+":8000/login";

    qDebug() << ip;

    QUrlQuery postData;
    postData.addQueryItem("username", username);
    postData.addQueryItem("password", password);

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    QNetworkRequest req;
    req.setUrl(QUrl(ipServer));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QNetworkReply *reply = manager->post(req,postData.toString(QUrl::FullyEncoded).toUtf8());

    while(!reply->isFinished()){
    qApp->processEvents();
    }

    QByteArray byteReply = reply->readAll();

    QJsonDocument jsonReply = QJsonDocument::fromJson(byteReply);
    QJsonObject replyObject = jsonReply.object();
    QJsonValue value = replyObject["Auth"];
    if( value.toBool() ){
        Player p(username,password);
        hide();
        mw = new Mainwindow(p,ip);
        mw->exec();
    } else{
        QMessageBox::warning(this,"Login Problem","Please check your username, password and ip");
    }
}

void FirstWindow::on_signUpPushButton_clicked()
{

    hide();
    sd = new SignUpDialog();
    sd->exec();

}
//abc 1
//user pass
//"http://localhost:8000/login"
