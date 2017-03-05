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

void Mainwindow::on_windowLoaded()
{
    ui->welocomeLabel->setText(ui->welocomeLabel->text() + plr.getPlayerName());
    std::thread forPics(&Mainwindow::setPics,this);
    updateBoard();
    forPics.join();
}

void Mainwindow::updateBoard()
{
    QUrlQuery postData;
    postData.addQueryItem("username", plr.getPlayerName());
    postData.addQueryItem("password", plr.getPassword());

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    QString ipServer = "http://"+ipaddress+":8000/details";

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

    QJsonValue displayGames = player["Games"];
    ui->gamesLabel->setText("Games Played : " + QString::number(displayGames.toInt()));
    QJsonValue displayScore = player["Points"];
    ui->pointsLabel->setText("Points Scored : " + QString::number(displayScore.toInt()));
    QJsonValue displayContri = player["Contri"];
    ui->contriLabel->setText("Contribution : " + QString::number(displayContri.toInt()));
}

void Mainwindow::hideWidgets()
{
}

void Mainwindow::setPics()
{
    QPixmap harryPotterPic(":/images/images/HarryPotter.png");
    ui->harryPotterPicLabel->setPixmap(harryPotterPic.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap gkPic(":/images/images/GK.png");
    ui->gkPicLabel->setPixmap(gkPic.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap moviesPic(":/images/images/movies.png");
    ui->moviesPicLabel->setPixmap(moviesPic.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap animePic(":/images/images/anime.png");
    ui->animePicLabel->setPixmap(animePic.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap computersPic(":/images/images/cs.png");
    ui->computersPicLabel->setPixmap(computersPic.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap sciencePic(":/images/images/science.png");
    ui->sciencePicLabel->setPixmap(sciencePic.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap gotPic(":/images/images/got.png");
    ui->gotPicLabel->setPixmap(gotPic.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap triviaPic(":/images/images/trivia.png");
    ui->triviaPicLabel->setPixmap(triviaPic.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap sportsPic(":/images/images/sports.png");
    ui->sportsPiclabel->setPixmap(sportsPic.scaled(100,100,Qt::KeepAspectRatio));
}

void Mainwindow::startGame(QString subject)
{
    //qDebug() << "MAin";
    hideWidgets();
    qDebug() << ipaddress;
    gw = new GameWindow(plr,subject, ipaddress);//Gamewindow(plr,subject);
    gw->exec();
    updateBoard();
}

void Mainwindow::showEvent(QShowEvent *ev)
{
    QDialog::showEvent(ev);
    emit window_loaded();
}

void Mainwindow::on_harryPotterPushButton_clicked()
{
    startGame("harrypotter");
}

void Mainwindow::on_gkPushButton_clicked()
{
    startGame("gk");
}

void Mainwindow::on_animePushButton_clicked()
{
    startGame("anime");
}

void Mainwindow::on_moviesPushButton_clicked()
{
    startGame("movies");
}

void Mainwindow::on_computersPushButton_clicked()
{
    startGame("computerscience");
}

void Mainwindow::on_sciencePushButton_clicked()
{
    startGame("science");
}

void Mainwindow::on_gotPushButton_clicked()
{
    startGame("got");
}

void Mainwindow::on_tiviaPushButton_clicked()
{
    startGame("trivia");
}

void Mainwindow::on_sportsPushButton_clicked()
{
    startGame("sports");
}

void Mainwindow::on_contributePushButton_clicked()
{
    cw = new Contribute(plr, ipaddress);
    cw->exec();
    updateBoard();
}
