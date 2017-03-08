/**
 * @file contribute.cpp
 * @author Vaibhav
 * @date 5 Mar 2017
 * @brief manages the opening contribute dialog
 *
 * This manages the contribute dialog.
 */
#include "contribute.h"
#include "ui_contribute.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QtNetwork>

/**
 * @brief Constructor for firstwindow
 *
 * Sets up the UI and some initial set up
 */
Contribute::Contribute(Player usr, QString ipaddress, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contribute)
{
    /* Set up UI */
    ui->setupUi(this);

    /* Make the TextEdit read only */
    ui->utiiltiyTextEdit->setReadOnly(true);

    /* Add choices */
    ui->choiceComboBox->addItem("1");
    ui->choiceComboBox->addItem("2");
    ui->choiceComboBox->addItem("3");
    ui->choiceComboBox->addItem("4");

    /* Add choices */
    ui->subjectComboBox->addItem("Harry Potter");
    ui->subjectComboBox->addItem("G K");
    ui->subjectComboBox->addItem("Movies");
    ui->subjectComboBox->addItem("Anime");
    ui->subjectComboBox->addItem("Computers");
    ui->subjectComboBox->addItem("Science");
    ui->subjectComboBox->addItem("GOT");
    ui->subjectComboBox->addItem("Trivia");
    ui->subjectComboBox->addItem("Sports");

    /*I(nitialize the member variables */
    plr = usr;
    ip = ipaddress;
}

Contribute::~Contribute()
{
    delete ui;
}

void Contribute::on_submitPushButton_clicked()
{

    /* Create the server Ip */
    QString ipServer = "http://"+ip+":8000/contri";

    /* Create the data that is to be posted*/
    QUrlQuery postData;
    postData.addQueryItem("username", plr.getPlayerName());
    postData.addQueryItem("password", plr.getPassword());
    postData.addQueryItem("question", ui->questionTextEdit->toPlainText());
    postData.addQueryItem("option1", ui->option1LineEdit->text());
    postData.addQueryItem("option2", ui->option2LineEdit->text());
    postData.addQueryItem("option3", ui->option3LineEdit->text());
    postData.addQueryItem("option4", ui->option4LineEdit->text());
    postData.addQueryItem("correct", ui->choiceComboBox->currentText());
    postData.addQueryItem("subject", ui->subjectComboBox->currentText().toLower());

    /* Convert the subject to lower before sening */
    ui->subjectComboBox->currentText().toLower();

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
    //qDebug() << replyObject;

    /* Display utility message */
    ui->utiiltiyTextEdit->setText("Thanks for contributing to APV Quiz. ");

    /* Clear all the feilds */
    ui->questionTextEdit->setText("");
    ui->option1LineEdit->setText("");
    ui->option2LineEdit->setText("");
    ui->option3LineEdit->setText("");
    ui->option4LineEdit->setText("");
}
