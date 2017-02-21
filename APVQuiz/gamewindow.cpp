#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QNetworkAccessManager>
#include <QtNetwork>
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
    ui->setupUi(this);
    timer = new QTimer(this);
    currentQuestionNumber = 1;

    connect(this, SIGNAL(window_loaded()), this, SLOT(on_windowLoaded()));
    connect(this,SIGNAL(timeout()),this,SLOT(updateTimer()));
}


GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_windowLoaded()
{
    ui->utilityLabel->setText("Looking for opponents ... ");
    QJsonObject reply = getQuestion(currentQuestionNumber);
    enableOptionButtons();
    setupQuestionAnswer(reply);
    starttime = new QTime(0,0,20);
    updateOpponentsBoard(reply);
    //currentQuestionNumber++;
}

void GameWindow::updateTimer()
{
    starttime->setHMS(0,0,starttime->addSecs(-1).second());
    QString remainingTime = starttime->toString().right(2);
    ui->timerLabel->setText(remainingTime);
    if(remainingTime == "00"){
        timer->stop();
        disableOptionButtons();
        qDebug() << "Time up ..";
        checkAnswer(0,0);
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
}

void GameWindow::updateOpponentsBoard(QJsonObject reply)
{
    QJsonArray opponentNameArray = reply["Opponents"].toArray();
    QJsonArray opponentScoreArray = reply["Scores"].toArray();

    ui->opponent1NameLabel->setText(opponentNameArray[0].toString());
    ui->opponent1Scorelabel->setText(opponentScoreArray[0].toString());
    ui->opponent2NameLabel->setText(opponentNameArray[1].toString());
    ui->opponent2Scorelabel->setText(opponentScoreArray[1].toString());
    ui->opponent3NameLabel->setText(opponentNameArray[2].toString());
    ui->opponent3Scorelabel->setText(opponentScoreArray[2].toString());
}

QJsonObject GameWindow::getQuestion(int q_number)
{
    QUrlQuery postData;
    postData.addQueryItem("username", plr.getPlayerName());
    postData.addQueryItem("password", plr.getPassword());
    postData.addQueryItem("subject",subject);

    QString url = "";//"http://localhost:8000"+"/play/"+subject+"/q"+q_number;

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QNetworkReply *reply = manager->post(req,postData.toString(QUrl::FullyEncoded).toUtf8());

    while(!reply->isFinished()){
    qApp->processEvents();
    }

    QByteArray questionInfoByteArray = reply->readAll();
    QJsonDocument questionInfo = QJsonDocument::fromJson(questionInfoByteArray);
    QJsonObject question = questionInfo.object();

    return question;
}

void GameWindow::setupQuestionAnswer(QJsonObject reply)
{
    QJsonValue question = reply["Question"];
    QJsonArray options = reply["Options"].toArray();
    QJsonValue ownScore = reply["Ownscore"];

    ui->questionLabel->setText(question.toString());
    ui->option1PushButton->setText(options[0].toString());
    ui->option2PushButton->setText(options[1].toString());
    ui->option3PushButton->setText(options[2].toString());
    ui->option4PushButton->setText(options[3].toString());
    ui->scoreLabel->setText(ownScore.toString());

    ui->utilityLabel->setText("");

    //start Timer
}

QJsonObject GameWindow::getResult(int choice,int time)
{
    QUrlQuery postData;
    postData.addQueryItem("username", plr.getPlayerName());
    postData.addQueryItem("password", plr.getPassword());
    postData.addQueryItem("subject",subject);
    postData.addQueryItem("choice",QString::number(choice));
    postData.addQueryItem("time",QString::number(time));

    QString url = "";//"http://localhost:8000"+"/play/"+subject+"/a"+q_number;

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QNetworkReply *reply = manager->post(req,postData.toString(QUrl::FullyEncoded).toUtf8());

    while(!reply->isFinished()){
    qApp->processEvents();
    }

    QByteArray replyInfoByteArray = reply->readAll();
    QJsonDocument replyInfo = QJsonDocument::fromJson(replyInfoByteArray);
    QJsonObject replyobject = replyInfo.object();

    return replyobject;
}

void GameWindow::proceedInGame()
{
    currentQuestionNumber++;
    if(currentQuestionNumber<6){
        QJsonObject reply = getQuestion(currentQuestionNumber);
        enableOptionButtons();
        setupQuestionAnswer(reply);
        starttime = new QTime(0,0,20);
        timer->start();
        updateOpponentsBoard(reply);
    }
    else{
        ui->utilityLabel->setText("Thanks for playing. Waiting for final scores");
        //Call the function which gets the final result
    }
}

void GameWindow::checkAnswer(int choice, int time)
{
    QJsonObject result = getResult(choice, time);

    switch (choice){
        case 1:
            ui->option1PushButton->setStyleSheet("background-color: rgb(255,0,0);");
        case 2:
            ui->option2PushButton->setStyleSheet("background-color: rgb(255,0,0);");
        case 3:
            ui->option3PushButton->setStyleSheet("background-color: rgb(255,0,0);");
        case 4:
            ui->option4PushButton->setStyleSheet("background-color: rgb(255,0,0);");
        //case 1:
            //ui->option1PushButton->setStyleSheet("background-color: rgb(255,0,0);");
    }

    QJsonValue correctOption = result["correctOption"];
    switch (correctOption.toInt()){
        case 1:
            ui->option1PushButton->setStyleSheet("background-color: rgb(0,255,0);");
        case 2:
            ui->option2PushButton->setStyleSheet("background-color: rgb(0,255,0);");
        case 3:
            ui->option3PushButton->setStyleSheet("background-color: rgb(0,255,0);");
        case 4:
            ui->option4PushButton->setStyleSheet("background-color: rgb(0,255,0);");
        //case 1:
            //ui->option1PushButton->setStyleSheet("background-color: rgb(255,0,0);");
    }

    proceedInGame();
}

void GameWindow::showEvent(QShowEvent *ev)
{
    QDialog::showEvent(ev);
    emit window_loaded();
}

void GameWindow::on_option1PushButton_clicked()
{
    timer->stop();
    QString timeOfAnswer = ui->timerLabel->text();
    checkAnswer(1,timeOfAnswer.toInt());
}
