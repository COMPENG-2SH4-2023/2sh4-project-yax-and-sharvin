#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs game(20, 10);
Player player = Player(&game);

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize();
    srand(static_cast<unsigned>(time(nullptr)));
    while (game.getExitFlagStatus() == false)
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
    MacUILib_init();
    MacUILib_clearScreen();
    objPos blockOff; // Assuming you have a specific position to block
    game.generateFood(blockOff);
}

void GetInput(void)
{
    // Asynchronous Input - non blocking character read-in
    if (MacUILib_hasChar())
    {
        game.setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{

    if (game.getInput() != 0) // if not null character
    {
        player.updatePlayerDir();

        if (game.getInput() == 'l')
        {
            game.setExitTrue();
        }

        if (game.getInput() == 'i')
        {
            game.incrementScore();
        }

        game.clearInput();
    }

    player.updatePlayerPos();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    //  Draw game instructions
    printf("WASD to move, space to exit\n\n");

    //  2. Iterate through each character location on the game board
    //     using the nested for-loop row-scanning setup.
    int i, j;
    for (i = 0; i < game.getBoardSizeY(); i++)
    {
        for (j = 0; j < game.getBoardSizeX(); j++)
        {
            // print character from list
            /*int k, t = 0;
            for (k = 0; k < 5; k++)
            {
                if (list[k].x == j && list[k].y == i)
                {
                    MacUILib_printf("%c", list[k].symbol);
                    t = 1;
                    break;
                }
            }
            if (t == 1)
            {
                continue;
            }*/

            objPosArrayList playerPosList;
            player.getPlayerPos(playerPosList);

            objPos foodPos;
            game.getFoodPos(foodPos);

            // top left corner
            if (i == 0 && j == 0)
            {
                cout << (char)201;
                continue;
            }
            // top right corner
            else if (i == 0 && j == game.getBoardSizeX() - 1)
            {
                cout << (char)187;
                continue;
            }
            // bottom left corner
            else if (i == game.getBoardSizeY() - 1 && j == 0)
            {
                cout << (char)200;
                continue;
            }
            // bottom right corner
            else if (i == game.getBoardSizeY() - 1 && j == game.getBoardSizeX() - 1)
            {
                cout << (char)188;
                continue;
            }
            else if (i == 0 || i == game.getBoardSizeY() - 1)
            {
                cout << (char)205;
                continue;
            }
            else if (j == 0 || j == game.getBoardSizeX() - 1)
            {
                cout << (char)186;
                continue;
            }
            else if (foodPos.x == j && foodPos.y == i)
            {
                cout << foodPos.symbol;
                continue;
            }
            else
            {
                
                // cout << playerPos.getSymbol();
            }


            printf(" ");
        }
        printf("\n");
    }

    // cout << "\nMystery String: " << mysteryString << endl;

    // print current position
    // objPos playerPos;
    // player.getPlayerPos(playerPos);
    // cout << "Current Position: " << playerPos.x << ", " << playerPos.y << endl;

    objPos foodPos;
    game.getFoodPos(foodPos);
    cout << "Current food pos: " << foodPos.x << ", " << foodPos.y << endl;

    // print score
    cout << "Score: " << game.getScore() << endl;
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    MacUILib_uninit();
}
