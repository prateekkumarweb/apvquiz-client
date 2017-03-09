/**
 * @file gamewindow.h
 * @author Vaibhav
 * @date 5 Mar 2017
 * @brief manages the openning first window
 *
 * Header file for the first window.
 */
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QTimer>
#include <QTcpSocket>
#include <QtWebSockets/QtWebSockets>
#include "Player.h"
namespace Ui {
class GameWindow;
}

/**
 * @brief Gamewindow class.
 *
 * Manages all activities of game window. Is live whenever game window is open.
 */
class GameWindow : public QDialog
{
    Q_OBJECT


public:
    /**
     * @brief Constructor for gamewindow
     *
     * Sets up the UI,
     * initializes member varibles formm the passed arguments
     * and connects signals to slots
     */
    explicit GameWindow(Player usr, QString sub, QString ip, QWidget *parent = 0);

    /**
     *@brief Destructor for game window
     *
     * Ends the window (Destroys the UI)
     */
    ~GameWindow();


    /* Documentation for each of the function can be obtained in the
     * corresponding mainwindow.cpp. The header contains all declaration.
     */

private slots:
    void on_windowLoaded();

    void updateTimer();

    void on_option1PushButton_clicked();

    void webSocketConnected();

    void webSocketDisconnected();

    void onWebSocketRead(QString message);

    void on_option2PushButton_clicked();

    void on_option3PushButton_clicked();

    void on_option4PushButton_clicked();



private :
    void disableOptionButtons();

    void enableOptionButtons();

    void updateOpponentsBoard(QString player1Name,QString player1Score,QString player2Name,QString player2Score);

    void setupQuestionAnswer(QString question, QString option1, QString option2, QString option3, QString option4, QString ownScore);

    void sendChoiceToServer(bool isCorrect, QString timeOfAnswer);

    void checkSelectedChoice(int choice);

    void handleButtonClicked(int buttonNumber);

    void reject();
protected:

      void showEvent(QShowEvent *ev);

signals:
      void window_loaded();

      void changeQuestionTextEdit(const QString &s);

private:
    Ui::GameWindow *ui; //!< Ui for this class
    Player plr; //!< A Player plr
    QString subject; //!< A String for subject
    QTimer *timer; //!< A QTimer pointer timer
    QTime *starttime; //!< A QTime pointer startttime
    int currentQuestionNumber; //!< An int for the current question number
    int correctAnswer; //!< An int for correct answer
    QString ipServer; //!< A string for ip
    QWebSocket webSocket; //!< A websocket for communication
    bool finalScoreRecieved; //!< A boolean to check if final score recieved
};

#endif // GAMEWINDOW_H
