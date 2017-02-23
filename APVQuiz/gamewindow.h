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

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(Player usr, QString sub, QWidget *parent = 0);
    ~GameWindow();

private slots:
    void on_windowLoaded();

    void updateTimer();

    void on_option1PushButton_clicked();

    void webSocketConnected();

    void webSocketDisconnected();

    void onWebSocketRead(QString message);

    //void socketWrote();

    //void getError(QAbstractSocket::SocketError);

private :
    void disableOptionButtons();

    void enableOptionButtons();

    void updateOpponentsBoard(QJsonObject reply);

    QJsonObject getQuestion(int q_number);

    void setupQuestionAnswer(QJsonObject reply);

    QJsonObject getResult(int choice,int time);

    void checkAnswer(int choice, int time);

    void proceedInGame();

    //void getTcp(int currentQuestionNumber);

protected:
      void showEvent(QShowEvent *ev);


signals:
      void window_loaded();

private:
    Ui::GameWindow *ui;
    Player plr;
    QString subject;
    QTimer *timer;
    QTime *starttime;
    int currentQuestionNumber;
    int currentRequesCondition;    //0 Question 1 Answer 2 Result
    //QTcpSocket *socket;
    QWebSocket webSocket;
};

#endif // GAMEWINDOW_H
