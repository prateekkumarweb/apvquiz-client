#include "contribute.h"
#include "ui_contribute.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QtNetwork>
Contribute::Contribute(Player usr, QString ipaddress, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contribute)
{
    ui->setupUi(this);
    ui->utiiltiyTextEdit->setReadOnly(true);

    ui->choiceComboBox->addItem("1");
    ui->choiceComboBox->addItem("2");
    ui->choiceComboBox->addItem("3");
    ui->choiceComboBox->addItem("4");

    ui->subjectComboBox->addItem("Harry Potter");
    ui->subjectComboBox->addItem("G K");
    ui->subjectComboBox->addItem("Movies");
    ui->subjectComboBox->addItem("Anime");
    ui->subjectComboBox->addItem("Computers");
    ui->subjectComboBox->addItem("Science");
    ui->subjectComboBox->addItem("GOT");
    ui->subjectComboBox->addItem("Trivia");
    ui->subjectComboBox->addItem("Sports");

    plr = usr;
    ip = ipaddress;
}

Contribute::~Contribute()
{
    delete ui;
}

void Contribute::on_pushButton_clicked()
{
    QString ipServer = "http://"+ip+":8000/contri";

    //qDebug() << ip;

    QUrlQuery postData;
    postData.addQueryItem("username", plr.getPlayerName());
    postData.addQueryItem("password", plr.getPassword());
    postData.addQueryItem("question", "");//ui->questionTextEdit->text());
    postData.addQueryItem("option1", ui->option1LineEdit->text());
    postData.addQueryItem("option2", ui->option2LineEdit->text());
    postData.addQueryItem("option3", ui->option3LineEdit->text());
    postData.addQueryItem("option4", ui->option4LineEdit->text());
    postData.addQueryItem("correct", ui->choiceComboBox->currentText());
    postData.addQueryItem("subject", ui->subjectComboBox->currentText());

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
    ui->utiiltiyTextEdit->setText("Thanks for cntributing to APV Quiz. ");
}
