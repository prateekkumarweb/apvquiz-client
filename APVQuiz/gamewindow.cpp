#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QDateTime>
#include <QTcpSocket>
#include <QtWebSockets/QtWebSockets>
GameWindow::GameWindow(Player usr, QString sub, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    //ui->utilityLabel->setText("Looking for opponents."+sub);
    setWindowTitle("Game");
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::Window);

    plr = usr;
    subject = sub;
    //currentRequestCondition = 0;
    ui->setupUi(this);
    timer = new QTimer(this);
    currentQuestionNumber = 0;

    connect(this, SIGNAL(window_loaded()), this, SLOT(on_windowLoaded()));
    connect(&webSocket,&QWebSocket::connected, this, &GameWindow::webSocketConnected);
    connect(&webSocket,&QWebSocket::disconnected, this, &GameWindow::webSocketDisconnected);
    connect(&webSocket,&QWebSocket::textMessageReceived, this, &GameWindow::onWebSocketRead);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTimer()));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_windowLoaded()
{
    ui->utilityLabel->setText("Looking for opponents ... ");
    //qDebug() << "Enter window";

    //socket->connectToHost("localhost", 6000);
    webSocket.open(QUrl("ws://localhost:8000/play"));
    //qDebug() << "Here";


    //updateOpponentsBoard(reply);
    //timer->start();
    //
}

void GameWindow::updateTimer()
{
    //qDebug() << "Timeout" << starttime->toString();
    starttime->setHMS(0,0,starttime->addSecs(-1).second());
    QString remainingTime = starttime->toString().right(2);
    ui->timerLabel->setText(remainingTime);
    if(remainingTime == "00"){
        timer->stop();
        disableOptionButtons();
        sendChoiceToServer(0,"0");
        checkSelectedChoice(0);
        //qDebug() << "Time up ..";
        //checkAnswer(0,0);
    }
}

void GameWindow::disableOptionButtons()
{
    ui->option1PushButton->setEnabled(false);
    ui->option2PushButton->setEnabled(false);
    ui->option3PushButton->setEnabled(false);
    ui->option4PushButton->setEnabled(false);
}

void GameWindow::enableOptionButtons()
{
    ui->option1PushButton->setEnabled(true);
    ui->option2PushButton->setEnabled(true);
    ui->option3PushButton->setEnabled(true);
    ui->option4PushButton->setEnabled(true);
    ui->option1PushButton->setStyleSheet("background-color: rgb(255,255,255);");
    ui->option2PushButton->setStyleSheet("background-color: rgb(255,255,255);");
    ui->option3PushButton->setStyleSheet("background-color: rgb(255,255,255);");
    ui->option4PushButton->setStyleSheet("background-color: rgb(255,255,255);");
}

void GameWindow::updateOpponentsBoard(QString player1Name,QString player1Score,QString player2Name,QString player2Score)
{
    ui->opponent1NameLabel->setText(player1Name);
    ui->opponent1Scorelabel->setText(player1Score);
    ui->opponent2NameLabel->setText(player2Name);
    ui->opponent2Scorelabel->setText(player2Score);
}

void GameWindow::setupQuestionAnswer(QString question, QString option1, QString option2, QString option3, QString option4, QString ownScore)
{
    ui->questionLabel->setText(question);
    ui->option1PushButton->setText(option1);
    ui->option2PushButton->setText(option2);
    ui->option3PushButton->setText(option3);
    ui->option4PushButton->setText(option4);
    ui->scoreLabel->setText(ownScore);

    ui->utilityLabel->setText("");

    //start Timer
}

void GameWindow::sendChoiceToServer(int choice, QString timeOfAnswer)
{
    webSocket.sendTextMessage(QString::number(choice));
    webSocket.sendTextMessage(timeOfAnswer);
}

void GameWindow::checkSelectedChoice(int choice)
{
    switch (choice){
        case 1:
            ui->option1PushButton->setStyleSheet("background-color: rgb(255,0,0);");
            break;
        case 2:
            ui->option2PushButton->setStyleSheet("background-color: rgb(255,0,0);");
            break;
        case 3:
            ui->option3PushButton->setStyleSheet("background-color: rgb(255,0,0);");
            break;
        case 4:
            ui->option4PushButton->setStyleSheet("background-color: rgb(255,0,0);");
            break;
    }

    switch (correctAnswer){
        case 1:
            ui->option1PushButton->setStyleSheet("background-color: rgb(0,255,0);");
            break;
        case 2:
            ui->option2PushButton->setStyleSheet("background-color: rgb(0,255,0);");
            break;
        case 3:
            ui->option3PushButton->setStyleSheet("background-color: rgb(0,255,0);");
            break;
        case 4:
            ui->option4PushButton->setStyleSheet("background-color: rgb(0,255,0);");
            break;
    }
}

/*
void GameWindow::checkAnswer(int choice, int time)
{
    QJsonObject result = getResult(choice, time);



    QJsonValue correctOption = result["correctOption"];
    switch (correctOption.toInt()){

    }

    proceedInGame();
}
*/
void GameWindow::showEvent(QShowEvent *ev)
{
    QDialog::showEvent(ev);
    emit window_loaded();
}

void GameWindow::webSocketConnected()
{
    qDebug() << "Conn";
    QString playerName= plr.getPlayerName();
    QString playerPassword = plr.getPassword();
    //Send subject;
    webSocket.sendTextMessage(playerName);
    webSocket.sendTextMessage(playerPassword);
    webSocket.flush();
    //webSocket.close();
}

void GameWindow::webSocketDisconnected()
{
    qDebug() << "DConn";
}

void GameWindow::onWebSocketRead(QString message)
{
    currentQuestionNumber++;
    if(currentQuestionNumber < 6){
        qDebug() << "message" << message;
        QString question, option1, option2, option3, option4, correctOption, ownScore, player1Name, player1Score, player2Name, player2Score;
        QRegExp rx ("(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)");
        rx.indexIn(message);
        question = rx.cap(1);
        option1 = rx.cap(2);
        option2 = rx.cap(3);
        option3 = rx.cap(4);
        option4 = rx.cap(5);
        correctOption = rx.cap(6);
        ownScore = rx.cap(7);
        player1Name = rx.cap(8);
        player1Score = rx.cap(9);
        player2Name = rx.cap(10);
        player2Score = rx.cap(11);
        setupQuestionAnswer(question, option1, option2, option3, option4, ownScore);
        starttime = new QTime(0,0,30);
        timer->start(1000);
        correctAnswer = correctOption.toInt();
        enableOptionButtons();
        updateOpponentsBoard(player1Name, player1Score, player2Name, player2Score);
    }
    else {
        //Show final results
    }
}
/*void GameWindow::socketWrote()
{
    qDebug() << "Wrt";
}
*/
void GameWindow::on_option1PushButton_clicked()
{
    timer->stop();
    qDebug() << "Option 1 clicked";
    disableOptionButtons();
    QString timeOfAnswer = ui->timerLabel->text();
    sendChoiceToServer(1, timeOfAnswer);
    checkSelectedChoice(1);
}

void GameWindow::on_option2PushButton_clicked()
{
    timer->stop();
    disableOptionButtons();
    qDebug() << "Option 2 clicked";
    QString timeOfAnswer = ui->timerLabel->text();
    sendChoiceToServer(2, timeOfAnswer);
    checkSelectedChoice(2);
}

void GameWindow::on_option3PushButton_clicked()
{
    timer->stop();
    disableOptionButtons();
    qDebug() << "Option 3 clicked";
    QString timeOfAnswer = ui->timerLabel->text();
    sendChoiceToServer(3, timeOfAnswer);
    checkSelectedChoice(3);
}

void GameWindow::on_option4PushButton_clicked()
{
    timer->stop();
    disableOptionButtons();
    qDebug() << "Option 4 clicked";
    QString timeOfAnswer = ui->timerLabel->text();
    sendChoiceToServer(4, timeOfAnswer);
    checkSelectedChoice(4);
}
