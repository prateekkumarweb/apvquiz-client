/**
 * @file signupdialog.cpp
 * @author Vaibhav
 * @date 5 Mar 2017
 * @brief manages the openning sign up dialog
 *
 * This manages the sign up dialog.
 */
#include "signupdialog.h"
#include "ui_signupdialog.h"

#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QtNetwork>

/**
 * @brief Constructor for signupdialog
 *
 * Sets up the UI
 */
SignUpDialog::SignUpDialog( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
}

/**
 * @brief Destructor for signup dialog
 *
 * Deletes the UI
 */
SignUpDialog::~SignUpDialog()
{
    /*Delete the UI */
    delete ui;
}

/**
 * @brief Slot for continue Button clicked
 *
 * Sends the server credentials for the new
 * user. Based on the reply of the user raises
 * error or continues to main window
 */
void SignUpDialog::on_continuePushButton_clicked()
{

    /* Get username, pasword and ip*/
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirPasswordLineEdit->text();
    QString ip = ui->ipLineEdit->text();
    QString ipServer = "http://"+ip+":8000/signup";

    /* If entered password and confirm passwords arre maatching then, */
    if(password == confirmPassword){

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
        QJsonValue statusValue = replyObject["Status"];
        QJsonValue message = replyObject["Message"];

        /* Proceed based on server's reply in Status */
        if(statusValue.toBool()){
            /* If player is authentic then proceed to main window */
            Player p(username,password);
            hide();
            mw = new Mainwindow(p,ip);
            mw->setFixedSize(954,640);
            mw->exec();
        } else {
            /* In case server replies problematic credentials, report the error */
            QMessageBox::warning(this,"Sign Up Error",message.toString());
        }

    } else{
        /* Rise an error for passwords mismatch */
        QMessageBox::warning(this,"Password Misamtch","The passwords don't match. Please try again");
    }

}
