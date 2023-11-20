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
  boardSizeX = boardX;
  boardSizeY = boardY;
  input = 0;
}

// do you need a destructor?

bool GameMechs::getExitFlagStatus()
{
  return exitFlag;
}

char GameMechs::getInput()
{
  return input;
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

void GameMechs::setInput(char this_input)
{
  input = this_input;
}

void GameMechs::clearInput()
{
  input = 0;
}
