/**
 * @file firstwindow.cpp
 * @author Vaibhav
 * @date 5 Mar 2017
 * @brief manages the openning first window
 *
 * This manages the first window.
 */
#include "firstwindow.h"
#include "ui_firstwindow.h"
#include <QMessageBox>

#include <QDebug>
#include <QNetworkAccessManager>
#include <QtNetwork>

/**
 * @brief Constructor for firstwindow
 *
 * Sets up the UI
 */
FirstWindow::FirstWindow( QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstWindow)
{
    /* Setup the UI */
    ui->setupUi(this);
}

FirstWindow::~FirstWindow()
{
    delete ui;
}

/**
 * @brief Slot for login Button clicked
 *
 * Sends the server credentials for verification and
 * raises error or continues to main window depending
 * on server reply.
 */
void FirstWindow::on_loginPushButton_clicked()
{

    /* Get username, pasword and ip*/
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString ip = ui->iplineEdit->text();
    QString ipServer = "http://"+ip+":8000/login";

    /* Create the data that is to pe posted*/
    QUrlQuery postData;
    postData.addQueryItem("username", username);
    postData.addQueryItem("password", password);

    /*Connect to server*/
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    /*send the data*/
    QNetworkRequest req;
    req.setUrl(QUrl(ipServer));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    /*Get (Wait) for reply) */
    QNetworkReply *reply = manager->post(req,postData.toString(QUrl::FullyEncoded).toUtf8());

    while(!reply->isFinished()){
    qApp->processEvents();
    }

    /* Parse the reply and check if server has validated user or not */
    QByteArray byteReply = reply->readAll();

    /* Convert the obtained bytearray to Json Object to parse */
    QJsonDocument jsonReply = QJsonDocument::fromJson(byteReply);
    QJsonObject replyObject = jsonReply.object();
    QJsonValue value = replyObject["Auth"];

    /* Proceed based on server's reply in Auth */
    if( value.toBool() ){
        /* If player is authentic then proceed to main window */
        Player p(username,password);
        hide();
        mw = new Mainwindow(p,ip);
        mw->exec();
    } else{
        /* In case server replies invalid credentials, report the error */
        QMessageBox::warning(this,"Login Problem","Please check your username, password and ip");
    }
}

/**
 * @brief Slot for Sign Up Button clicked
 *
 * Exits the current window and opens signup window.
 */
void FirstWindow::on_signUpPushButton_clicked()
{
    /* Create the sign up dialog and hide the current first window */
    hide();
    sd = new SignUpDialog();
    sd->exec();

}
//abc 1
//user pass
