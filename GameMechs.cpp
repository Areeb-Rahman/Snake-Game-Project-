#include "GameMechs.h"


GameMechs::GameMechs() // default constructor
{
    input = '\0';
    exitFlag = 0;
    loseFlag = 0;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;

    food = objPos();
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\0';
    exitFlag = 0;
    loseFlag = 0;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;

    food = objPos();
}

// do you need a destructor? No because nothing is created on the heap

bool GameMechs::getExitFlagStatus() const // done
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const // done
{
    return loseFlag;
}

char GameMechs::getInput() const // done
{
    return input;
}

int GameMechs::getScore() const // done
{
    return score;
}

void GameMechs::incrementScoreBy(int amount) // done
{
    // increase score by 1
    score += amount;
}

int GameMechs::getBoardSizeX() const // done
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const // done
{
    return boardSizeY;
}

void GameMechs::setExitTrue() // done
{
    exitFlag = true;
}

void GameMechs::setLoseFlag() // done
{

    loseFlag = true;
}

void GameMechs::setInput(char this_input) // done
{
    input = this_input;
}

void GameMechs::clearInput() // done
{
    input = '\0';
}

// More methods should be added here