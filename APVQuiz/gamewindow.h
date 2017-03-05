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
    explicit GameWindow(Player usr, QString sub, QString ip, QWidget *parent = 0);
    ~GameWindow();

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
    Ui::GameWindow *ui;
    Player plr;
    QString subject;
    QTimer *timer;
    QTime *starttime;
    int currentQuestionNumber;
    int correctAnswer;
    QString ipServer;
    QWebSocket webSocket;
};

#endif // GAMEWINDOW_H
