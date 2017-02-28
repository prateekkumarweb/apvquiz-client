#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QDateTime>
#include <QTcpSocket>
#include <QtWebSockets/QtWebSockets>

#include <thread>
GameWindow::GameWindow(Player usr, QString sub, QString ip, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    //setWindowTitle("Game");
    //Qt::WindowFlags flags = windowFlags();
    //setWindowFlags(flags | Qt::Window);

    plr = usr;
    subject = sub;
    ui->setupUi(this);
    timer = new QTimer(this);
    currentQuestionNumber = 0;
    qDebug() << "ip is" << ip;
    ipServer = "ws://"+ip+":8000/play";
    qDebug() << "ipServer " << ipServer;

    connect(this, SIGNAL(window_loaded()), this, SLOT(on_windowLoaded()));
    connect(&webSocket,&QWebSocket::connected, this, &GameWindow::webSocketConnected);
    connect(&webSocket,&QWebSocket::disconnected, this, &GameWindow::webSocketDisconnected);
    connect(&webSocket,&QWebSocket::textMessageReceived, this, &GameWindow::onWebSocketRead);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTimer()));
}

GameWindow::~GameWindow()
{
    //Send to server (Game left)
    qDebug() << "Closing app";
    webSocket.sendTextMessage("closed");
    delete ui;
}

void GameWindow::on_windowLoaded()
{
    ui->questionTextEdit->setReadOnly(true);
    ui->utilityLabel->setText("Looking for opponents ... ");
    disableOptionButtons();

    qDebug() << "ip" << ipServer;
    webSocket.open(QUrl(ipServer));
}

void GameWindow::updateTimer()
{
    starttime->setHMS(0,0,starttime->addSecs(-1).second());
    QString remainingTime = starttime->toString().right(2);
    ui->timerLabel->setText(remainingTime);
    if(remainingTime == "00"){
        disableOptionButtons();
        timer->stop();        
        sendChoiceToServer(0,"0");
        checkSelectedChoice(0);
    }
}

void GameWindow::disableOptionButtons()            //Part
{
    ui->option1PushButton->setEnabled(false);
    ui->option2PushButton->setEnabled(false);
    ui->option3PushButton->setEnabled(false);
    ui->option4PushButton->setEnabled(false);
}

void GameWindow::enableOptionButtons()          //Part                                                                                                          //Part
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

void GameWindow::updateOpponentsBoard(QString player1Name,QString player1Score,QString player2Name,QString player2Score)                            //Part
{
    ui->opponent1NameLabel->setText(player1Name);
    ui->opponent1Scorelabel->setText(player1Score);
    ui->opponent2NameLabel->setText(player2Name);
    ui->opponent2Scorelabel->setText(player2Score);
}

void GameWindow::setupQuestionAnswer(QString question, QString option1, QString option2, QString option3, QString option4, QString ownScore)       //Part
{
    ui->questionTextEdit->setText(question);
    ui->option1PushButton->setText(option1);
    ui->option2PushButton->setText(option2);
    ui->option3PushButton->setText(option3);
    ui->option4PushButton->setText(option4);
    ui->scoreLabel->setText(ownScore);

    ui->utilityLabel->setText("");

    //start Timer
}

void GameWindow::sendChoiceToServer(bool isCorrect, QString timeOfAnswer)   //Part
{
    qDebug() << "here" << isCorrect;
    webSocket.sendTextMessage(QString::number(isCorrect));
    webSocket.sendTextMessage(timeOfAnswer);
}

void GameWindow::checkSelectedChoice(int choice)                //Part
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

void GameWindow::handleButtonClicked(int buttonNumber)          //Ys
{
    timer->stop();
    QString timeOfAnswer = ui->timerLabel->text();
    bool isCorrect = buttonNumber==correctAnswer;
    //qDebug() << "Option 1 clicked";
    std::thread forDisablingButtons(&GameWindow::disableOptionButtons, this);
    std::thread forChecking(&GameWindow::checkSelectedChoice, this, buttonNumber);
    sendChoiceToServer(isCorrect, timeOfAnswer);
    forDisablingButtons.join();
    forChecking.join();
}

void GameWindow::showEvent(QShowEvent *ev)              //NO
{
    QDialog::showEvent(ev);
    emit window_loaded();
}

void GameWindow::webSocketConnected()                   //NO
{
    qDebug() << "Conn";
    QString playerName= plr.getPlayerName();
    QString playerPassword = plr.getPassword();
    //Send subject;
    webSocket.sendTextMessage(playerName);
    webSocket.sendTextMessage(playerPassword);
    webSocket.sendTextMessage(subject);
    webSocket.flush();
    //webSocket.close();
}

void GameWindow::webSocketDisconnected()                //NO
{
    qDebug() << "DConn";
}

void GameWindow::onWebSocketRead(QString message)       //YES
{
    qDebug() << "message" << message;
    currentQuestionNumber++;
    if(message != "Opponent has left the game"){
        if(currentQuestionNumber < 6){

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
            enableOptionButtons();
            updateOpponentsBoard(player1Name, player1Score, player2Name, player2Score);
            correctAnswer = correctOption.toInt();
            /*qDebug() << "here before";
            std::thread forQA(&GameWindow::setupQuestionAnswer,this,question, option1, option2, option3, option4, ownScore);
            qDebug() << "here after";
            std::thread forEnablingButtons(&GameWindow::enableOptionButtons, this);
            qDebug() << "here after";
            std::thread forUpdatingBoard(&GameWindow::updateOpponentsBoard,this,player1Name, player1Score, player2Name, player2Score);
            qDebug() << "here after";
            correctAnswer = correctOption.toInt();
            qDebug() << "here after";
            forQA.join();
            qDebug() << "here after";
            forEnablingButtons.join();
            qDebug() << "here after";
            forUpdatingBoard.join();
            qDebug() << "here after";*/
            ui->timerLabel->setText("20");
            starttime = new QTime(0,0,20);
            timer->start(1000);
        }
        else {
            qDebug() << "message" << message;
            QString ownScore, player1Name, player1Score, player2Name, player2Score;
            QRegExp rx ("(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)");
            rx.indexIn(message);
            ownScore = rx.cap(1);
            player1Name = rx.cap(2);
            player1Score = rx.cap(3);
            player2Name = rx.cap(4);
            player2Score = rx.cap(5);
            std::thread forUpdatingBoard(&GameWindow::updateOpponentsBoard,this,player1Name, player1Score, player2Name, player2Score);
            ui->scoreLabel->setText(ownScore);
            if(ownScore.toInt() >= player1Score.toInt() && ownScore.toInt() >= player2Score.toInt()){
                ui->utilityLabel->setText("Congratulations you stood first, with final score "+ownScore);
            }
            else if(ownScore.toInt() < player1Score.toInt() && ownScore.toInt() < player2Score.toInt()){
                ui->utilityLabel->setText("You finished third, with final score "+ownScore);
            }
            else{
                ui->utilityLabel->setText("Congratulations you stood second, with final score "+ownScore);
            }
            forUpdatingBoard.join();
        }
    }
    else{
        timer->stop();
        ui->utilityLabel->setText("Sorry ... Your opponent has left the quiz. We will add your current points to your total. ");
    }

}
/*void GameWindow::socketWrote()
{
    qDebug() << "Wrt";
}
*/
void GameWindow::on_option1PushButton_clicked()             //Ys
{
    handleButtonClicked(1);
}

void GameWindow::on_option2PushButton_clicked()             //Ys
{
    handleButtonClicked(2);
}

void GameWindow::on_option3PushButton_clicked()             //Ys
{
    handleButtonClicked(3);
}

void GameWindow::on_option4PushButton_clicked()             //Ys
{
    handleButtonClicked(4);
}

void GameWindow::reject()
{
    qDebug() << "Closing app";
    webSocket.sendTextMessage("closed");
    QDialog::reject();
}
