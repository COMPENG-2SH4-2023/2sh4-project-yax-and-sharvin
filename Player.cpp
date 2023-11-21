#include "Player.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.x = 9;
    playerPos.y = 9;
    playerPos.symbol = '*';
}

Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos array list
    returnPos = playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}
