#include "Player.h"

Player::Player(QString name, QString pass)
{
    username = name;
    password = pass;
}

Player::Player()
{

}

QString Player::getPlayerName()
{
    return username;
}

QString Player::getPassword()
{
    return password;
}
