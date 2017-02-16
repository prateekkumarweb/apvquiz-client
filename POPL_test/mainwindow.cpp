#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QtNetwork>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timermanage()));
    starttime = new QTime(0,0,20);
    //timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logInPushButton_clicked()
{
    //ui->offlineLabel->setText("There was a connection problem.\n Please check your network.");
    //ui->offlineTextBrowser->setText("There was a connection problem. Please check your network.");
    QString clicktime = ui->label->text();
    timer->stop();
    qDebug() << "Time at which login button clicked " << clicktime;
    ui->logInPushButton->setStyleSheet("background-color: rgb(255,0,0);");

   /* QVariantMap top;
    //qDebug() << ui->usernameTextEdit->text();
    top.insert( "username" , QString( ui->usernameLabel->text() ) );
    top.insert( "password", QString( ui->passwordLabel->text() ) );
    const QJsonDocument doc = QJsonDocument::fromVariant(top);
    QByteArray postData = doc.toJson();

    qDebug() << doc << postData;*/

    QUrlQuery postData;
    postData.addQueryItem("username", "prateek");
    postData.addQueryItem("password", "pass");

    //QNetworkRequest request(serviceUrl);
    //request.setHeader(QNetworkRequest::ContentTypeHeader,
    //   "application/x-www-form-urlencoded");
    //networkManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    QNetworkRequest req;
    req.setUrl(QUrl("http://localhost:8000/login"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QNetworkReply *reply = manager->post(req,postData.toString(QUrl::FullyEncoded).toUtf8());

    while(!reply->isFinished())
    {
    qApp->processEvents();
    }

    QByteArray s = reply->readAll();

    QJsonDocument docv = QJsonDocument::fromJson(s);
    QJsonObject sett2 = docv.object();
    QJsonValue value = sett2["Auth"];
    qWarning() << value.toBool();

    //qDebug() << s;

}

void MainWindow::timermanage()
{
    QTime time = QTime::currentTime();
    starttime->setHMS(0,0,starttime->addSecs(-1).second());
    //ui->label->text(starttime->toString());
    QString remainingTime = starttime->toString().right(2);
    ui->label->setText(remainingTime);
    if(remainingTime == "00"){
        timer->stop();
        qDebug() << "Time up ..";
    }
    //qDebug() << "Update ..";
}
