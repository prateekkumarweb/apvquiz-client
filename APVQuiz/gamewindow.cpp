/**
 * @file gamewindow.cpp
 * @author Vaibhav
 * @date 5 Mar 2017
 * @brief manages the opening game window
 *
 * This manages the main window.
 */
#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QDateTime>
#include <QTcpSocket>
#include <QtWebSockets/QtWebSockets>

#include <thread>

/**
 * @brief Constructor for gamewindow
 *
 * Sets up the UI,
 * initializes member varibles formm the passed arguments
 * and connects signals to slots
 */
GameWindow::GameWindow(Player usr, QString sub, QString ip, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    /*set the member variables using the parameters passed */
    plr = usr;
    subject = sub;
    ipServer = "ws://"+ip+":8000/play";

    /* Setup the UI */
    ui->setupUi(this);

    /* Instantiate timer */
    timer = new QTimer(this);

    /* Initialize currentQuestionNumber with 0 and finalScoreRecieved with false */
    currentQuestionNumber = 0;
    finalScoreRecieved = false;

    /* Connect the signal window_loaded() to the SLOT on_windowLoaded() */
    connect(this, SIGNAL(window_loaded()), this, SLOT(on_windowLoaded()));

    /*  Connect the signal changeQuestionTextEdit to the SLOT setText */
    connect(this, &GameWindow::changeQuestionTextEdit, ui->questionTextEdit, &QTextEdit::setText);

    /* Connect the signals of websocket to appropriate SLOTs */
    connect(&webSocket,&QWebSocket::connected, this, &GameWindow::webSocketConnected);
    connect(&webSocket,&QWebSocket::disconnected, this, &GameWindow::webSocketDisconnected);
    connect(&webSocket,&QWebSocket::textMessageReceived, this, &GameWindow::onWebSocketRead);

    /* Connect SIGNAL timeout to SLOT updateTimer */
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTimer()));
}

/**
 * @brief Distructor for gamewindow
 *
 * ends UI
 */
GameWindow::~GameWindow()
{
    delete ui;
}

/**
 * @brief Slot to handle signal window_loaded()
 *
 * Connects to Server, disables options and
 * does other utility tasks
 */
void GameWindow::on_windowLoaded()
{
    /* Make questionTextEdit readOnly */
    ui->questionTextEdit->setReadOnly(true);

    /* Display utility message */
    ui->utilityLabel->setText("Looking for opponents ... ");

    /*Disable options */
    disableOptionButtons();

    /* Connect to server */
    webSocket.open(QUrl(ipServer));
}

/**
 * @brief Slot to handle signal timeout()
 *
 * Responsible for maintaining dislplay timer and
 * take appropriate action in case time runs to 0
 */
void GameWindow::updateTimer()
{
    /* Decrement starttime by 1 sec */
    starttime->setHMS(0,0,starttime->addSecs(-1).second());

    /* Get the remaining seconds */
    QString remainingTime = starttime->toString().right(2);

    /* Set the value of remaaining time in the timer */
    ui->timerLabel->setText(remainingTime);

    /* If time runs out */
    if(remainingTime == "00"){
        \
        /*Disable the option buttons*/
        disableOptionButtons();

        /* Stop the timer */
        timer->stop();

        /*Send the server that no choice was selected */
        sendChoiceToServer(0,"0");

        /*Send to checking function */
        checkSelectedChoice(0);
    }
}

/**
 * @brief Function to disable the option buttons
 *
 * Responsible for disabling option buttons
 * To be called whenever time is up or user clicked a choice
 */
void GameWindow::disableOptionButtons()
{
    /*Disable all the option buttons */
    ui->option1PushButton->setEnabled(false);
    ui->option2PushButton->setEnabled(false);
    ui->option3PushButton->setEnabled(false);
    ui->option4PushButton->setEnabled(false);
}

/**
 * @brief Function to enable the option buttons
 *
 * Responsible for enabling option buttons
 * To be called whenever a new question is set up
 */
void GameWindow::enableOptionButtons()                                                                                                                   //Part
{
    /* Enable all the option buttons */
    ui->option1PushButton->setEnabled(true);
    ui->option2PushButton->setEnabled(true);
    ui->option3PushButton->setEnabled(true);
    ui->option4PushButton->setEnabled(true);

    /* Reset the colours of all buttons back to white */
    ui->option1PushButton->setStyleSheet("background-color: rgb(255,255,255);");
    ui->option2PushButton->setStyleSheet("background-color: rgb(255,255,255);");
    ui->option3PushButton->setStyleSheet("background-color: rgb(255,255,255);");
    ui->option4PushButton->setStyleSheet("background-color: rgb(255,255,255);");
}

/**
 * @brief Function to update the opponents board
 *
 * Responsible for updating the opponents board
 * using the parameters passed
 */
void GameWindow::updateOpponentsBoard(QString player1Name,QString player1Score,QString player2Name,QString player2Score)                            //Part
{
    /*Set up the usernaame and score of the 2 opponents */
    ui->opponent1NameLabel->setText(player1Name);
    ui->opponent1Scorelabel->setText(player1Score);
    ui->opponent2NameLabel->setText(player2Name);
    ui->opponent2Scorelabel->setText(player2Score);
}

/**
 * @brief Function to setup the question, own-score and options
 *
 * Responsible for setting up the question and and options
 * using the parameters passed
 */
void GameWindow::setupQuestionAnswer(QString question, QString option1, QString option2, QString option3, QString option4, QString ownScore)       //Part
{
    /* Set up the question */
    emit changeQuestionTextEdit("Question " + QString::number(currentQuestionNumber) + "\n" + question);

    /* Set up the options */
    ui->option1PushButton->setText(option1);
    ui->option2PushButton->setText(option2);
    ui->option3PushButton->setText(option3);
    ui->option4PushButton->setText(option4);

    /* Set up own Score */
    ui->scoreLabel->setText(ownScore);

    /* Display utility message */
    ui->utilityLabel->setText("");
}

/**
 * @brief Function to send the selected choice and time to server
 *
 * Responsible for sending the selected choice and time to server
 */
void GameWindow::sendChoiceToServer(bool isCorrect, QString timeOfAnswer)
{
    /*Send  server the selected option and the time of answer */
    webSocket.sendTextMessage(QString::number(isCorrect));
    webSocket.sendTextMessage(timeOfAnswer);
}

/**
 * @brief Function to check the selected choice
 *
 * Responsible for checking the selected choice
 */
void GameWindow::checkSelectedChoice(int choice)
{
    /* Set the colour of the selected option to RED */
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

    /* Set the colour of the correct option to GREEN */
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

/**
 * @brief Function to handle option click
 *
 * Responsible for handling button (@param buttonNumber) clicked
 */
void GameWindow::handleButtonClicked(int buttonNumber)
{
    /* Stop the timer */
    timer->stop();

    /* Get the time left */
    QString timeOfAnswer = ui->timerLabel->text();

    /* Check if the answer clicked is correct */
    bool isCorrect = buttonNumber==correctAnswer;

    /* Start a thread which disables the options */
    std::thread forDisablingButtons(&GameWindow::disableOptionButtons, this);

    /*Start another thread which checks the selected choice*/
    std::thread forChecking(&GameWindow::checkSelectedChoice, this, buttonNumber);

    /* Meanwhile send the selected choice and the time of answer to server */
    sendChoiceToServer(isCorrect, timeOfAnswer);

    /*Join with the thread that was disbling buttonss */
    forDisablingButtons.join();

    /*Join with the threaad thaat was checking the clicked option */
    forChecking.join();
}

/**
 * @brief Overridden showEvent function
 *
 * Overridden showEvent function first calls its
 * parent's showEvent function and then emitss SIGNAL
 * window_loaded()
 */
void GameWindow::showEvent(QShowEvent *ev)
{
    /* Call Parent's showEvent function */
    QDialog::showEvent(ev);

    /* emit the signal window_loaded() */
    emit window_loaded();
}

/**
 * @brief SLOT to handle SIGNAL websocket::Connected
 *
 * Send the server the user credentials aand subject
 */
void GameWindow::webSocketConnected()
{
    /* Get the username and the password */
    QString playerName= plr.getPlayerName();
    QString playerPassword = plr.getPassword();

    /* Send the server username, password and subject */
    webSocket.sendTextMessage(playerName);
    webSocket.sendTextMessage(playerPassword);
    webSocket.sendTextMessage(subject);

    /*Flush the websocket */
    webSocket.flush();
}

/**
 * @brief SLOT to handle SIGNAL websocket::Disconnected
 *
 * Acknowledge the disconnection
 */
void GameWindow::webSocketDisconnected()
{
    qDebug() << "WebSocket DisConnected";
}

/**
 * @brief SLOT to handle SIGNAL websocket::textMessageReceived
 *
 * Parses the @param message recieved and does one of the following
 * Starts up a new question
 * Displays the final score
 * Handles opposition leaving the game
 */
void GameWindow::onWebSocketRead(QString message)
{
    qDebug() << "message" << message;
    /* Increment currentQuestionNumber */
    currentQuestionNumber++;

    /*If the message is not Opponent has left the game */
    if(message != "Opponent has left the game"){

        /*If the currentQuestionNumber is less than 6 */
        if(currentQuestionNumber < 6){

            /* Declare variables */
            QString question, option1, option2, option3, option4, correctOption, ownScore, player1Name, player1Score, player2Name, player2Score;

            /*create a regular expression to parse the message */
            QRegExp rx ("(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)");

            /*Parse the message and store them in appropriate strings */
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

            /* Start a thread that enables the option buttons */
            //std::thread forEnablingButtons(&GameWindow::enableOptionButtons, this);

            enableOptionButtons();

            /*Start a thread that updates the Opponents' board */
            std::thread forUpdatingBoard(&GameWindow::updateOpponentsBoard,this,player1Name, player1Score, player2Name, player2Score);

            /*Meanwhile on the parent thread setup the question, options and the score */
            setupQuestionAnswer(question, option1, option2, option3, option4, ownScore);

            /* Set the member variable */
            correctAnswer = correctOption.toInt();

            /*Wait for the thread that enabled buttons to complete */
            //forEnablingButtons.join();

            /* Wait for the thread that updated the opponents board to complete */
            forUpdatingBoard.join();

            /* Set the timer value to 20 */
            ui->timerLabel->setText("20");

            /*Initialize the starttime variable */
            starttime = new QTime(0,0,20);

            /* Strat the timer */
            timer->start(1000);
        }
        else {
            //qDebug() << "message" << message;

            /* Set finalScoreRecieved to true */
            finalScoreRecieved = true;

            /* Declare variables */
            QString ownScore, player1Name, player1Score, player2Name, player2Score;

            /*create a regular expression to parse the message */
            QRegExp rx ("(.*)@#@(.*)@#@(.*)@#@(.*)@#@(.*)");

            /*Parse the message and store them in appropriate strings */
            rx.indexIn(message);
            ownScore = rx.cap(1);
            player1Name = rx.cap(2);
            player1Score = rx.cap(3);
            player2Name = rx.cap(4);
            player2Score = rx.cap(5);

            /*Start a thread that updates the Opponents' board */
            std::thread forUpdatingBoard(&GameWindow::updateOpponentsBoard,this,player1Name, player1Score, player2Name, player2Score);

            /*Meanwhile on the parent thread compare own scrore with opponents' and displaay the final result */
            ui->scoreLabel->setText(ownScore);
            if(ownScore.toInt() >= player1Score.toInt() && ownScore.toInt() >= player2Score.toInt()){
                /* User stands first */
                ui->utilityLabel->setText("Congratulations you stood first, with final score "+ownScore);
            }
            else if(ownScore.toInt() < player1Score.toInt() && ownScore.toInt() < player2Score.toInt()){
                /* User stands third */
                ui->utilityLabel->setText("You finished third, with final score "+ownScore);
            }
            else{
                /* User stands second */
                ui->utilityLabel->setText("Congratulations you stood second, with final score "+ownScore);
            }

            /* Wait for the thread that updated the opponents board to complete */
            forUpdatingBoard.join();
        }
    }
    else if (!finalScoreRecieved){
        /*In case the questions are not over but some opponent left the game */

        /*Stop the timer*/
        timer->stop();

        /*Disable the option buttons */
        disableOptionButtons();

        /* Display utility message */
        ui->utilityLabel->setText("Sorry ... Your opponent has left the quiz. We will add your current points to your total. ");
    }
}

/**
 * @brief SLOT to handle SIGNAL option1 button click
 *
 * Handles the button click
 */
void GameWindow::on_option1PushButton_clicked()
{
    handleButtonClicked(1);
}

/**
 * @brief SLOT to handle SIGNAL option2 button click
 *
 * Handles the button click
 */
void GameWindow::on_option2PushButton_clicked()
{
    handleButtonClicked(2);
}

/**
 * @brief SLOT to handle SIGNAL option3 button click
 *
 * Handles the button click
 */
void GameWindow::on_option3PushButton_clicked()
{
    handleButtonClicked(3);
}

/**
 * @brief SLOT to handle SIGNAL option4 button click
 *
 * Handles the button click
 */
void GameWindow::on_option4PushButton_clicked()
{
    handleButtonClicked(4);
}

/**
 * @brief Overridden reject function
 *
 * Overridden reject function first calls its
 * parent's showEvent function and then emitss SIGNAL
 * window_loaded()
 */
void GameWindow::reject()
{
    qDebug() << "Closing app rej";

    /* Close the websocket*/
    webSocket.close();

    /*Call the parent reject */
    QDialog::reject();
}

// 2 + (1+1)
