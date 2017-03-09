#include "Player.h"

/**
 * @brief Constructor for Player
 *
 * Initializes member variables based on @param name
 * and @param pass
 */
Player::Player(QString name, QString pass)
{
    /* Set the username and password according top the parameters */
    username = name;
    password = pass;
}

/**
 * @brief Constructor for Player
 *
 * Empty constructor
 */
Player::Player()
{

}

/**
 * @brief Destructor for Player
 */
Player::~Player()
{

}

/**
 * @brief Function to get the player name
 *
 * @return Returns the username of the player
 */
QString Player::getPlayerName()
{
    return username;
}

/**
 * @brief Function to get the player password
 *
 * @return Returns the paassword of the player
 */
QString Player::getPassword()
{
    return password;
}
