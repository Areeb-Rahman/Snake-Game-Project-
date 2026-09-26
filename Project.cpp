#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include <cstdlib>
#include <ctime>

using namespace std;

#define DELAY_CONST 100000

// GLOBAL Variables
GameMechs *gameMechanics;

bool exitFlag;
Player *player;
Food *food;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (exitFlag == false)
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

    srand(time(NULL)); 

    exitFlag = false;

    gameMechanics = new GameMechs();

    player = new Player(gameMechanics); //making  a new player object 

    food = new Food(gameMechanics);
    objPos playerStartPos;
    player->getPlayerPos(playerStartPos); // contains start position of player
    food->generateFoods(playerStartPos);   // generate food while avoiding player position

}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        char c = MacUILib_getChar();
        gameMechanics->setInput(c);

        if (c == ' ' || c == ' ') // exit keybind  
            gameMechanics->setExitTrue();
    }
}

void RunLogic(void)
{
    exitFlag = gameMechanics->getExitFlagStatus();

    player->updatePlayerDir();

    //food collision detection
    objPos head;
    player->getPlayerPos(head);

    objPosArrayList foods;
    food->getFoodPos(foods);

    bool ate_food = false;

    char eatenSymbol;
    int eatenIndex = -1;


    //check if any food eaten
    for (int i = 0; i < foods.getSize(); i++)
    {
        objPos element = foods.getElement(i);

        if (head.isPosEqual(&element))
        {
            ate_food = true;
            eatenSymbol = element.symbol;
            eatenIndex = i;
            break;
        }
    }
    bool grow = ate_food;
    int extraGrow =0;

    if (ate_food)
    {
        if (eatenSymbol == '!') //if ! is eaten score + 10, no change in length
        {
            gameMechanics->incrementScoreBy(10);
            grow = false;
        }
        else if(eatenSymbol == '$') //if & eaten score +50, but length increases by 5
        {
            gameMechanics->incrementScoreBy(50);
            extraGrow =4;
        }
        else 
        {
            gameMechanics->incrementScoreBy(1);
        }
    }
    player->movePlayer(grow);

    for (int i=0; i<extraGrow;i++) //grow by 9 (in total length increases by 10)
    {
        player->movePlayer(true);
    }

    // if ate food make new food & give score
    if (ate_food)
    {
        objPos newHead;
        player->getPlayerPos(newHead);
        food->generateFoods(newHead);
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    int width = gameMechanics->getBoardSizeX();
    int height = gameMechanics->getBoardSizeY();

    //getting player body postion 
    objPosArrayList body;
    player->getPlayerBody(body);

    //get food postion
    objPosArrayList foods;
    food->getFoodPos(foods);


    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            bool printed = false;

            // borders # 
            if (row == 0 || row == height - 1 || col == 0 || col == width - 1)
            {
                MacUILib_printf("#");
                continue;
            }

            //drawing snake 
            for (int i = 0; i < body.getSize(); i++)
            {
                objPos segment = body.getElement(i);

                int sx = segment.pos->x;
                int sy = segment.pos->y;

                if (row == sy && col == sx)
                {
                    MacUILib_printf("%c", segment.symbol);
                    printed = true;
                    break;
                }
            }
            if (printed) continue;

            // Draw food

            for (int i=0;i<foods.getSize();i++)
            {
                objPos f = foods.getElement(i);
                if (row ==f.pos->y && col == f.pos->x)
                {
                    MacUILib_printf("%c",f.symbol);
                    printed =true;
                    break;
                }    
            }
            if (printed) continue;

            //empty spaces 
            MacUILib_printf(" ");
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d\n",gameMechanics->getScore());
    MacUILib_printf("$: 50 POINTS BUT 10 LENGTH INCREASES BY 10\n");
    MacUILib_printf("!: 10 POINTS");
    MacUILib_printf("\nPress SPACEBAR to Quit");
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST);
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    MacUILib_printf("You Lost");
    MacUILib_printf("\nScore: %d", gameMechanics->getScore());
    delete player;
    delete gameMechanics;
    delete food;
    MacUILib_uninit();
}
