#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *game;
Player *player;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize();

    while (game->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    game = new GameMechs(30, 15);
    player = new Player(game);

    objPos pos;
    player->getPlayerPos(pos);

    player->getPlayerPosList();

    game->generateFood(player->getPlayerPosList());

    srand(time(NULL));

    MacUILib_init();
    MacUILib_clearScreen();
}

void GetInput(void)
{
    char input = game->getInput();
    game->setInput(input);
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();

    if (game->getInput() != 0) // if not null character
    {
        if (game->getInput() == 'l')
        {
            game->setExitTrue();
        }

        if (game->getInput() == 'i')
        {
            game->incrementScore();
        }

        if (game->getInput() == 'r')
        {
            game->generateFood(player->getPlayerPosList());

            objPos foodPos;
            game->getFoodPos(foodPos);
        }
    }

    game->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    //  Draw game instructions
    printf("WASD to move, space to exit\n\n");

    objPos playerHead;
    player->getPlayerPos(playerHead);

    objPosArrayList *playerPosList = player->getPlayerPosList();

    objPos foodPos;
    game->getFoodPos(foodPos);

    //  2. Iterate through each character location on the game board
    //     using the nested for-loop row-scanning setup.
    for (int i = 0; i < game->getBoardSizeY(); i++)
    {
        for (int j = 0; j < game->getBoardSizeX(); j++)
        {
            // if border
            if (i == 0 || i == game->getBoardSizeY() - 1 || j == 0 || j == game->getBoardSizeX() - 1)
            {
                // top left corner
                if (i == 0 && j == 0)
                {
                    MacUILib_printf("%c", (char)201);
                }
                // top right corner
                else if (i == 0 && j == game->getBoardSizeX() - 1)
                {
                    MacUILib_printf("%c", (char)187);
                }
                // bottom left corner
                else if (i == game->getBoardSizeY() - 1 && j == 0)
                {
                    MacUILib_printf("%c", (char)200);
                }
                // bottom right corner
                else if (i == game->getBoardSizeY() - 1 && j == game->getBoardSizeX() - 1)
                {
                    MacUILib_printf("%c", (char)188);
                }
                // top and bottom borders
                else if (i == 0 || i == game->getBoardSizeY() - 1)
                {
                    MacUILib_printf("%c", (char)205);
                }
                // left and right borders
                else if (j == 0 || j == game->getBoardSizeX() - 1)
                {
                    MacUILib_printf("%c", (char)186);
                }

                continue;
            }

            else if (foodPos.x == j && foodPos.y == i)
            {
                MacUILib_printf("%c", foodPos.symbol);
                continue;
            }
            else
            {
                bool isPlayer = false;
                for (int k = 0; k < playerPosList->getSize(); k++)
                {
                    objPos pos;
                    playerPosList->getElement(pos, k);

                    if (pos.x == j && pos.y == i)
                    {
                        MacUILib_printf("%c", pos.getSymbol());
                        isPlayer = true;
                        break;
                    }
                }
                if (isPlayer)
                {
                    continue;
                }
            }

            printf(" ");
        }
        printf("\n");
    }

    // cout << "\nMystery String: " << mysteryString << endl;

    // print current position
    objPos playerPos;
    playerPosList->getHeadElement(playerPos);
    cout << "Current Position: " << playerPos.x << ", " << playerPos.y << endl;

    cout << "Current food pos: " << foodPos.x << ", " << foodPos.y << endl;

    // print score
    cout << "Score: " << game->getScore() << endl;
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    if (game->getLoseFlagStatus())
    {
        MacUILib_printf("You lose!\n");
    }
    MacUILib_printf("You scored %d points!\n", game->getScore());

    MacUILib_uninit();
}
