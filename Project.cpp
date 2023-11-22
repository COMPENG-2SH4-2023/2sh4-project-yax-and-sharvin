#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs game = GameMechs(20, 10);
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

            objPos playerPos;
            player.getPlayerPos(playerPos);

            // top left corner
            if (i == 0 && j == 0)
            {
                cout << (char)201;
            }
            // top right corner
            else if (i == 0 && j == game.getBoardSizeX() - 1)
            {
                cout << (char)187;
            }
            // bottom left corner
            else if (i == game.getBoardSizeY() - 1 && j == 0)
            {
                cout << (char)200;
            }
            // bottom right corner
            else if (i == game.getBoardSizeY() - 1 && j == game.getBoardSizeX() - 1)
            {
                cout << (char)188;
            }
            else if (i == 0 || i == game.getBoardSizeY() - 1)
            {
                cout << (char)205;
            }
            else if (j == 0 || j == game.getBoardSizeX() - 1)
            {
                cout << (char)186;
            }
            else if (playerPos.x == j && playerPos.y == i)
            {
                cout << playerPos.getSymbol();
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    // cout << "\nMystery String: " << mysteryString << endl;

    // print current position
    objPos playerPos;
    player.getPlayerPos(playerPos);
    cout << "Current Position: " << playerPos.x << ", " << playerPos.y << endl;
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
