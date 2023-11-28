#include "Player.h"
#include "objPos.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();

    playerPos = objPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');
    playerPosList->insertTail(playerPos);
}

Player::~Player()
{
    delete playerPosList;
}

Player::Player(const Player &player)
{
    // copy constructor
    mainGameMechsRef = player.mainGameMechsRef;
    myDir = player.myDir;
    playerPos = player.playerPos;
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos = playerPos;
}

objPosArrayList *Player::getPlayerPosList()
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic

    char input = mainGameMechsRef->getInput();

    if (input == 0)
    {
        return;
    }

    switch (input)
    {
    case ' ': // exit
        mainGameMechsRef->setExitTrue();
        break;

        // up
    case 'W':
    case 'w':
        if (getDir() != Player::DOWN)
        {
            setDir(Player::UP);
        };
        break;

        // down
    case 'S':
    case 's':
        if (getDir() != Player::UP)
        {
            setDir(Player::DOWN);
        };
        break;

        // left
    case 'A':
    case 'a':
        if (getDir() != Player::RIGHT)
        {
            setDir(Player::LEFT);
        };
        break;

        // right
    case 'D':
    case 'd':
        if (getDir() != Player::LEFT)
        {
            setDir(Player::RIGHT);
        };
        break;

    default:
        break;
    }
}

void Player::movePlayer()
{
    objPos head;
    playerPosList->getHeadElement(head);

    // update the player location
    if (getDir() != STOP)
    {

        switch (getDir())
        {
        case UP:
            head.y--;
            break;

        case DOWN:
            head.y++;
            break;

        case LEFT:
            head.x--;
            break;

        case RIGHT:
            head.x++;
            break;

        default:
            break;
        }
    }

    // border wraparound
    if (head.x <= 0)
    {
        head.x = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if (head.x >= mainGameMechsRef->getBoardSizeX() - 1)
    {
        head.x = 1;
    }
    else if (head.y <= 0)
    {
        head.y = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if (head.y >= mainGameMechsRef->getBoardSizeY() - 1)
    {
        head.y = 1;
    }

    playerPosList->insertHead(head);

    // check if player is touching the food
    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos);

    if (foodPos.isPosEqual(&head))
    {
        mainGameMechsRef->incrementScore();

        // generate new food
        mainGameMechsRef->generateFood(playerPosList);
    }
    else
    {
        // remove last element
        playerPosList->removeTail();
    }

    if (checkSelfCollision())
    {
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }
}

Player::Dir Player::getDir()
{
    return myDir;
}

bool Player::checkSelfCollision()
{
    objPos head;
    playerPosList->getHeadElement(head);

    for (int i = 1; i < playerPosList->getSize(); i++)
    {

        objPos segment;
        playerPosList->getElement(segment, i);

        if (head.isPosEqual(&segment))
        {
            return true;
        }
    }

    return false;
}

void Player::setDir(Dir thisDir)
{
    myDir = thisDir;
}