#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
  exitFlag = false;
  boardSizeX = 20;
  boardSizeY = 20;
  input = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
  exitFlag = false;
  loseFlag = false;
  boardSizeX = boardX;
  boardSizeY = boardY;
  input = 0;
  score = 0;
  srand(static_cast<unsigned>(time(nullptr)));
}

bool GameMechs::getExitFlagStatus()
{
  return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
  return loseFlag;
}

char GameMechs::getInput()
{
  if (MacUILib_hasChar() != 0)
  {
    input = MacUILib_getChar();
  }
  return input;
}

void GameMechs::incrementScore()
{
  score++;
}

int GameMechs::getScore()
{
  return score;
}

int GameMechs::getBoardSizeX()
{
  return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
  return boardSizeY;
}

void GameMechs::setExitTrue()
{
  exitFlag = true;
}

void GameMechs::setLoseFlag()
{
  loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
  input = this_input;
}

void GameMechs::clearInput()
{
  input = 0;
}

void GameMechs::generateFood(objPosArrayList *blockOff)
{
  // make sure that there is space for food to be generated
  if (blockOff->getSize() >= (boardSizeX - 2) * (boardSizeY - 2))
  {
    setExitTrue();
    return;
  }

  // Ensure the generated position is not the same as blockOff
  while (true)
  {
    foodPos.x = rand() % (boardSizeX - 2) + 1;
    foodPos.y = rand() % (boardSizeY - 2) + 1;
    foodPos.symbol = 'X';

    bool hitFlag = false;
    for (int i = 0; i < blockOff->getSize(); i++)
    {
      objPos pos;
      blockOff->getElement(pos, i);

      if (foodPos.x == pos.x && foodPos.y == pos.y)
      {
        hitFlag = true;
        break;
      }
    }

    if (!hitFlag)
    {
      break;
    }
  }
}

void GameMechs::getFoodPos(objPos &returnPos)
{
  returnPos = foodPos;
}