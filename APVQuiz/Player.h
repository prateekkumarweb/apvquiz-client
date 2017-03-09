/**
 * @file Player.h
 * @author Vaibhav
 * @date 5 Mar 2017
 * @brief Manages player
 *
 * Header file for the palyer.
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

/**
 * @brief Player class.
 *
 * Manages a player.
 */
class Player
{
    QString username; //!< member variable player's username
    QString password; //!< member variable player's password

public:
    /**
     * @brief Constructor for Player
     *
     * Initializes member variables based on @param name
     * and @param pass
     */
    Player(QString name, QString pass);

    /**
     * @brief Constructor for Player
     *
     * Empty constructor
     */
    Player();

    /**
     * @brief Destructor for Player
     */
    ~Player();

    /**
     * @brief Function to get the player name
     *
     * @return Returns the username of the player
     */
    QString getPlayerName();

    /**
     * @brief Function to get the player password
     *
     * @return Returns the paassword of the player
     */
    QString getPassword();
};

#endif // PLAYER_H
