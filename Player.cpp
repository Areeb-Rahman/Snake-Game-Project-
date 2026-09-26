#include "Player.h"
#include "Food.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef; // defining 
    myDir = STOP; //default enum is stop 

    // more actions to be included
    player_body = new objPosArrayList();
    objPos snake_head;
    snake_head.setObjPos(5, 5, '*'); //! change starting position
    player_body->insertHead(snake_head);

    
}

Player::~Player()
{
    // delete any heap members here
    delete player_body;
}

void Player::getPlayerPos(objPos &returnPos) const
{
    // return the reference to the playerPos arrray list
    returnPos = player_body->getHeadElement();
}

void Player::updatePlayerDir()
{
    //get input
    char input = mainGameMechsRef->getInput();

    //valutate Enum value
    switch (input)
    {
    case 'w':
    case 'W':
        if (myDir != DOWN)

            myDir = UP;
        break;

    case 's':
    case 'S':
        if (myDir != UP)
            myDir = DOWN;
        break;

    case 'a':
    case 'A':
        if (myDir != RIGHT)
            myDir = LEFT;
        break;
    case 'd':
    case 'D':
        if (myDir != LEFT)
            myDir = RIGHT;
        break;
    };

    /// clear input

    mainGameMechsRef->clearInput();
}
//getter metjod 
void Player::getPlayerBody(objPosArrayList &output_list) const
{
    for (int i = 0; i < player_body->getSize(); i++)
    {
        output_list.insertTail(player_body->getElement(i));
    }
}
//function to move player in 2d array based on current postion and enum direction 
void Player::movePlayer(bool grow)
{    //player position
    objPos snake_head = player_body->getHeadElement();
    int x = snake_head.pos->x;
    int y = snake_head.pos->y;
    char symbol = snake_head.symbol;

    //board information
    int max_y = mainGameMechsRef->getBoardSizeY();
    int max_x = mainGameMechsRef->getBoardSizeX();
    int min_x = 0;
    int min_y = 0;
    // moving player
    switch (myDir)
    {
    case UP:   // check case
        y--;   // increment + or - by 1 for corresponding axis
        break; // break to ensure no extra actions are taken

    case DOWN:
        y++;
        break;

    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

    default:
        break;
    }

    ///wrap around logic
    //lower bounds
    if (x <= 0)
        x = max_x - 2;
    if (y <= 0)
        y = max_y - 2;
    //upper bound
    if (x >= max_x - 1)
        x = 1;
    if (y >= max_y - 1)
        y = 1;

    // calculare new position
    objPos new_snake_head;
    new_snake_head.setObjPos(x, y, '*');

    // placing new head on board
    player_body->insertHead(new_snake_head);
    if (!grow)
    {
        player_body->removeTail();
    }


    //check self-collision
    objPos dummy;
    getPlayerPos(dummy);
    if (checkSelfCollision(dummy))
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }

}

// More methods to be added
//check collision with food 
bool Player::checkFoodCollision(const objPos &foodPos)
{
    objPos head = player_body->getHeadElement(); //get location of player head 
    return head.isPosEqual(&foodPos);  //use isequal method to check if x,y player is the same as x,y food for a specified food obkect 
}

bool Player::checkSelfCollision(const objPos &playerPos) 
{
    objPos snakehead = player_body->getHeadElement(); // gets pos of head
    int snake_length = player_body->getSize(); 

    for (int i=1; i< snake_length; i++)
    {
        objPos snake_segment = player_body->getElement(i); //gets i-th elements
        
        if (snakehead.isPosEqual(&snake_segment))
        {
            return true;
        }
        
    }
    return false; 
}
