#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Player.h"

#include <QPixmap>
#include <QNetworkAccessManager>
#include <QtNetwork>

#include <thread>
Mainwindow::Mainwindow(Player usr, QString ip, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
    setWindowTitle("APV Quiz");
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::Window);
    plr = usr;
    ipaddress = ip;

    connect(this, SIGNAL(window_loaded()), this, SLOT(on_windowLoaded()));
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::on_harryPotterPushButton_clicked()
{
    startGame("harryPotter");
}

void Mainwindow::on_gkPushButton_clicked()
{
    startGame("gk");
}

void Mainwindow::on_bollywoodPushButton_clicked()
{
    startGame("bollywood");
}

void Mainwindow::on_hollywodPushButton_clicked()
{
    startGame("hollywood");
}

void Mainwindow::on_windowLoaded()
{
    std::thread forPics(&Mainwindow::setPics,this);
    //std::thread forBoardUpdation(updateboard);
    //setPics();
    //updateboard();
    ui->welocomeLabel->setText(ui->welocomeLabel->text() + plr.getPlayerName());
    int games = 12;
    ui->gamesLabel->setText(ui->gamesLabel->text() + QString::number(games));
    int pts = 12;
    ui->pointsLabel->setText(ui->pointsLabel->text() + QString::number(pts));
    int contri = 12;
    ui->contriLabel->setText(ui->contriLabel->text() + QString::number(contri));
    forPics.join();
    //forBoardUpdation(updateBoard);

}

void Mainwindow::updateBoard()
{
    QUrlQuery postData;
    postData.addQueryItem("username", plr.getPlayerName());
    postData.addQueryItem("password", plr.getPassword());

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    QString ipServer = "http://"+ipaddress+"/sth";

    QNetworkRequest req;
    req.setUrl(QUrl(ipServer));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QNetworkReply *reply = manager->post(req,postData.toString(QUrl::FullyEncoded).toUtf8());

    while(!reply->isFinished()){
    qApp->processEvents();
    }

    QByteArray playerInfoByteArray = reply->readAll();
    QJsonDocument playerInfo = QJsonDocument::fromJson(playerInfoByteArray);
    QJsonObject player = playerInfo.object();
    QJsonValue displayName = player["Name"];
    ui->welocomeLabel->setText(ui->welocomeLabel->text() + displayName.toString());
    QJsonValue displayScore = player["Score"];
    ui->gamesLabel->setText(ui->gamesLabel->text() + QString::number(displayScore.toInt()));
    QJsonValue displayContri = player["Contri"];
    ui->contriLabel->setText(ui->contriLabel->text() + QString::number(displayContri.toInt()));
}

void Mainwindow::hideWidgets()
{
   // QVBoxLayout *board = ui->boardVerticalLayout;
   //(*board)::hide();
   //ui->gamesGridLayout::hide();
    //QGridLayout *g = ui->gamesGridLayout;
    //g->hide();
    //g->QWidget::hide();
}

void Mainwindow::setPics()
{
    QPixmap harryPotterPic(":/images/images/Harry-Potter-Hat.ico");
    ui->harryPotterPicLabel->setPixmap(harryPotterPic.scaled(64,64,Qt::KeepAspectRatio));
    QPixmap gkPic(":/images/images/gk.png");
    ui->gkPicLabel->setPixmap(gkPic.scaled(64,64,Qt::KeepAspectRatio));
    QPixmap bollywoodPic(":/images/images/bollywood.png");
    ui->bollywoodPicLabel->setPixmap(bollywoodPic.scaled(64,64,Qt::KeepAspectRatio));
    QPixmap hollywoodPic(":/images/images/hollywood.jpg");
    ui->hollywoodPicLabel->setPixmap(hollywoodPic.scaled(64,64,Qt::KeepAspectRatio));
}

void Mainwindow::startGame(QString subject)
{
    //qDebug() << "MAin";
    qDebug() << ipaddress;
    gw = new GameWindow(plr,subject, ipaddress);//Gamewindow(plr,subject);
    gw->exec();
}

void Mainwindow::showEvent(QShowEvent *ev)
{
    QDialog::showEvent(ev);
    emit window_loaded();
}
