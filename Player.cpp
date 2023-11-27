#include "Player.h"
#include "objPos.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.x = 9;
    playerPos.y = 9;
    playerPos.symbol = '*';

    playerPosList = new objPosArrayList();
}

Player::~Player()
{
    // delete any heap members here
}

Player::Player(const Player &player)
{
    // copy constructor
    mainGameMechsRef = player.mainGameMechsRef;
    myDir = player.myDir;
    playerPos = player.playerPos;
}

void Player::getPlayerPos(objPosArrayList &returnPosList)
{
    // deferenece the pointer
    returnPosList = *playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic

    switch (mainGameMechsRef->getInput())
    {
    case ' ': // exit
        mainGameMechsRef->setExitTrue();
        break;

        // DIRECTION CONTROL
    case 'w': // up
        if (getDir() != Player::DOWN)
        {
            setDir(Player::UP);
        };
        break;

    case 's': // down
        if (getDir() != Player::UP)
        {
            setDir(Player::DOWN);
        };
        break;

    case 'a': // left
        if (getDir() != Player::RIGHT)
        {
            setDir(Player::LEFT);
        };
        break;

    case 'd': // right
        if (getDir() != Player::LEFT)
        {
            setDir(Player::RIGHT);
        };
        break;

    default:
        break;
    }
}

void Player::updatePlayerPos()
{
    int newX = playerPos.x;
    int newY = playerPos.y;

    // update the player location
    if (getDir() != STOP)
    {

        switch (getDir())
        {
        case UP:
            newY--;
            break;

        case DOWN:
            newY++;
            break;

        case LEFT:
            newX--;
            break;

        case RIGHT:
            newX++;
            break;

        default:
            break;
        }
    }

    // border wraparound
    if (newX <= 0)
    {
        newX = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if (newX >= mainGameMechsRef->getBoardSizeX() - 1)
    {
        newX = 1;
    }
    else if (newY <= 0)
    {
        newY = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if (newY >= mainGameMechsRef->getBoardSizeY() - 1)
    {
        newY = 1;
    }

    objPos newPlayerPos;
    newPlayerPos.x = newX;
    newPlayerPos.y = newY;
    newPlayerPos.symbol = playerPos.getSymbol();

    // playerPos.setObjPos(newPlayerPos);


    playerPosList->insertHead(newPlayerPos);

    // remove last element
    playerPosList->removeTail();
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

Player::Dir Player::getDir()
{
    return myDir;
}

void Player::setDir(Dir thisDir)
{
    myDir = thisDir;
}