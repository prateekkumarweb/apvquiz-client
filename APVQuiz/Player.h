#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
class Player
{
    QString username;
    QString password;

public:
    Player(QString name, QString pass);

    Player();

    QString getPlayerName();

    QString getPassword();
};

#endif // PLAYER_H
