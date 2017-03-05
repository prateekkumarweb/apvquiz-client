/**
 * @file mainwindow.cpp
 * @author Vaibhav
 * @date 5 Mar 2017
 * @brief manages the opening main window
 *
 * This manages the main window.
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Player.h"

#include <QPixmap>
#include <QNetworkAccessManager>
#include <QtNetwork>

#include <thread>

/**
 * @brief Constructor for mainwindow
 *
 * Sets up the UI, converts to window from dialog
 * and initializes member varibles formm the passed arguments
 */
Mainwindow::Mainwindow(Player usr, QString ip, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mainwindow)
{
    /* Setup the UI */
    ui->setupUi(this);

    /* Convert thios dialog to window */
    setWindowTitle("APV Quiz");
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::Window);

    /* Initialize member variables using the passed argumnets */
    plr = usr;
    ipaddress = ip;

    /* Connect the signal window_loaded() to the SLOT on_windowLoaded() */
    connect(this, SIGNAL(window_loaded()), this, SLOT(on_windowLoaded()));
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

/**
 * @brief Slot to handle signal window_loaded()
 *
 * Sets up the pictures of the subjects and
 * also sets up the player board
 */
void Mainwindow::on_windowLoaded()
{
    /* Set the player name */
    ui->welocomeLabel->setText(ui->welocomeLabel->text() + plr.getPlayerName());

    /* Strat a thread that sets up the pictures */
    std::thread forPics(&Mainwindow::setPics,this);

    /* Update the player board */
    updateBoard();

    /* Wait for the thread to finish execution */
    forPics.join();
}

/**
 * @brief Updates the player board
 *
 * Updates the player board by recieveing data
 * from the server
 */
void Mainwindow::updateBoard()
{
    /* Create the data that is to be posted*/
    QUrlQuery postData;
    postData.addQueryItem("username", plr.getPlayerName());
    postData.addQueryItem("password", plr.getPassword());

    /*Connect to server*/
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    /* Set up the ip */
    QString ipServer = "http://"+ipaddress+":8000/details";

    /*send the data*/
    QNetworkRequest req;
    req.setUrl(QUrl(ipServer));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    /*Get (Wait) for reply) */
    QNetworkReply *reply = manager->post(req,postData.toString(QUrl::FullyEncoded).toUtf8());

    while(!reply->isFinished()){
    qApp->processEvents();
    }

    /* parse the reply and convert to Json Object */
    QByteArray playerInfoByteArray = reply->readAll();
    QJsonDocument playerInfo = QJsonDocument::fromJson(playerInfoByteArray);
    QJsonObject player = playerInfo.object();

    /* Get values from the json and update the player board using that */
    QJsonValue displayGames = player["Games"];
    ui->gamesLabel->setText("Games Played : " + QString::number(displayGames.toInt()));
    QJsonValue displayScore = player["Points"];
    ui->pointsLabel->setText("Points Scored : " + QString::number(displayScore.toInt()));
    QJsonValue displayContri = player["Contri"];
    ui->contriLabel->setText("Contribution : " + QString::number(displayContri.toInt()));
}

/**
 * @brief Sets up the Pictures  to display
 *
 * Set up the pictures that are to be displayed
 * for each subject
 */
void Mainwindow::setPics()
{
    /* Get the pixmap of harry potter and display at appropriate position */
    QPixmap harryPotterPic(":/images/images/HarryPotter.png");
    ui->harryPotterPicLabel->setPixmap(harryPotterPic.scaled(100,100,Qt::KeepAspectRatio));

    /* Get the pixmap of gk and display at appropriate position */
    QPixmap gkPic(":/images/images/GK.png");
    ui->gkPicLabel->setPixmap(gkPic.scaled(100,100,Qt::KeepAspectRatio));

    /* Get the pixmap of movies and display at appropriate position */
    QPixmap moviesPic(":/images/images/movies.png");
    ui->moviesPicLabel->setPixmap(moviesPic.scaled(100,100,Qt::KeepAspectRatio));

    /* Get the pixmap of anime and display at appropriate position */
    QPixmap animePic(":/images/images/anime.png");
    ui->animePicLabel->setPixmap(animePic.scaled(100,100,Qt::KeepAspectRatio));

    /* Get the pixmap of computers and display at appropriate position */
    QPixmap computersPic(":/images/images/cs.png");
    ui->computersPicLabel->setPixmap(computersPic.scaled(100,100,Qt::KeepAspectRatio));

    /* Get the pixmap of  and display at appropriate position */
    QPixmap sciencePic(":/images/images/science.png");
    ui->sciencePicLabel->setPixmap(sciencePic.scaled(100,100,Qt::KeepAspectRatio));

    /* Get the pixmap of got and display at appropriate position */
    QPixmap gotPic(":/images/images/got.png");
    ui->gotPicLabel->setPixmap(gotPic.scaled(100,100,Qt::KeepAspectRatio));

    /* Get the pixmap of trivia and display at appropriate position */
    QPixmap triviaPic(":/images/images/trivia.png");
    ui->triviaPicLabel->setPixmap(triviaPic.scaled(100,100,Qt::KeepAspectRatio));

    /* Get the pixmap of sports and display at appropriate position */
    QPixmap sportsPic(":/images/images/sports.png");
    ui->sportsPiclabel->setPixmap(sportsPic.scaled(100,100,Qt::KeepAspectRatio));
}

/**
 * @brief Starts the game
 *
 * Starts the game based on the (@param subject)
 * chosen by the player
 */
void Mainwindow::startGame(QString subject)
{
    /* Start the game window */
    gw = new GameWindow(plr,subject, ipaddress);
    gw->exec();

    /* When the game ends update the board again */
    updateBoard();
}

/**
 * @brief Overridden showEvent function
 *
 * Overridden showEvent function first calls its
 * parent's showEvent function and then emitss SIGNAL
 * window_loaded()
 */
void Mainwindow::showEvent(QShowEvent *ev)
{
    /* Call Parent's showEvent function */
    QDialog::showEvent(ev);

    /* emit the signal window_loaded() */
    emit window_loaded();
}

/**
 * @brief SLOT to handle the click of harry potter button
 *
 * starts game taking harry potter as subject
 */
void Mainwindow::on_harryPotterPushButton_clicked()
{
    startGame("harrypotter");
}

/**
 * @brief SLOT to handle the click of gk button
 *
 * starts game taking gk as subject
 */
void Mainwindow::on_gkPushButton_clicked()
{
    startGame("gk");
}

/**
 * @brief SLOT to handle the click of anime button
 *
 * starts game taking anime as subject
 */
void Mainwindow::on_animePushButton_clicked()
{
    startGame("anime");
}

/**
 * @brief SLOT to handle the click of movies button
 *
 * starts game taking movies as subject
 */
void Mainwindow::on_moviesPushButton_clicked()
{
    startGame("movies");
}

/**
 * @brief SLOT to handle the click of computers button
 *
 * starts game taking computters as subject
 */
void Mainwindow::on_computersPushButton_clicked()
{
    startGame("computerscience");
}

/**
 * @brief SLOT to handle the click of science button
 *
 * starts game taking science as subject
 */
void Mainwindow::on_sciencePushButton_clicked()
{
    startGame("science");
}

/**
 * @brief SLOT to handle the click of got button
 *
 * starts game taking got as subject
 */
void Mainwindow::on_gotPushButton_clicked()
{
    startGame("got");
}

/**
 * @brief SLOT to handle the click of trivia button
 *
 * starts game taking trivia as subject
 */
void Mainwindow::on_tiviaPushButton_clicked()
{
    startGame("trivia");
}

/**
 * @brief SLOT to handle the click of sports button
 *
 * starts game taking sports as subject
 */
void Mainwindow::on_sportsPushButton_clicked()
{
    startGame("sports");
}

/**
 * @brief SLOT to handle the click of contribute button
 *
 * creates the contribue dialog
 */
void Mainwindow::on_contributePushButton_clicked()
{
    /* Start the contribute dialog */
    cw = new Contribute(plr, ipaddress);
    cw->exec();

    /* After contribution update the board again */
    updateBoard();
}
