#include "GameMechs.h"

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

// do you need a destructor?

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

void GameMechs::setLoseTrue()
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

void GameMechs::generateFood(objPos blockOff)
{

  // Ensure the generated position is not the same as blockOff
  while ((foodPos.x == blockOff.x && foodPos.y == blockOff.y) || (foodPos.x == 0 && foodPos.y == 0))
  {
    foodPos.x = 1 + rand() % (boardSizeX - 2);
    foodPos.y = 1 + rand() % (boardSizeY - 2);
  }

  foodPos.symbol = '0';
}

void GameMechs::getFoodPos(objPos &returnPos)
{
  returnPos = foodPos;
}