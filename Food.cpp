#include "Food.h"



Food::~Food() //deconstructor
{   
    delete foodBucket;
}

Food::Food(GameMechs* thisGMRef) //constructor
{
    gameMechRef = thisGMRef;  // Store the reference
    foodBucket = new objPosArrayList();

    objPos dummy;
    dummy.setObjPos(-2,-2,' ');

    generateFoods(dummy);
}

void Food::getFoodPos(objPosArrayList &returnList) const //getter
{
    for (int i=0; i<foodBucket->getSize();i++)
    {
        returnList.insertTail(foodBucket->getElement(i));
    }
}



void Food::generateFoods(objPos blockOff)
{
    int i=0,j=0,k=0;
    int candidateX;
    int candidateY;
    int validPosition;
    int xRange = gameMechRef->getBoardSizeX();
    int yRange = gameMechRef->getBoardSizeY();
    int counter =0; 

    while (foodBucket->getSize() >0)
    {
        foodBucket->removeTail();
    }

    

    while (counter <5){  //5 is the max number of food allowed on the screen at a time
        //random position generation 
        validPosition = 0;
        //generate random candidate coordinates
        while (validPosition != 1)
        {
<<<<<<< HEAD
            candidateX = (rand() % (xRange - 2)) + 1; //generates random X coordinate within range
            candidateY = (rand() % (yRange - 2)) + 1; //generates random Y coordinate within range

            // ensure candidate doesn't intefere with player 
            objPos blockedCopy = blockOff.getObjPos(); //position that is alread taken
=======
            candidateX = (rand() % (xRange - 2)) + 1; //generate random X coordinate within range
            candidateY = (rand() % (yRange - 2)) + 1; //generate random Y coordinate within range

            //candidate doesn't intefere with player 
            objPos blockedCopy = blockOff.getObjPos(); //position that is already taken
>>>>>>> 9305d433a938fb296f124384bdf1534fdbfda9e4
            int playerCollision=0;
            if (candidateX == blockedCopy.pos->x && candidateY == blockedCopy.pos->y) 
            {
                playerCollision =1;
            }
        
            //no conflicts
            if (playerCollision ==0)
            {   
                //normal or special food
                char symbol;
                int random_num = rand() % 10;

                if (random_num ==0)
                {
                    symbol = '!'; //special type 1 
                }
                else if (random_num ==1)
                {
                    symbol = '$'; //special type 2 
                }
                else
                {
                    symbol = 'F'; //normal
                }

                objPos newFood;
                newFood.setObjPos(candidateX,candidateY,symbol); //sets the positions (x and y) to candidateX and candidateY which do not conflict with any other object on board

<<<<<<< HEAD
                foodBucket->insertTail(newFood); 
=======
                foodBucket->insertTail(newFood); //new food information is added to the arraylist which carries all food information (position and symbol)
>>>>>>> 9305d433a938fb296f124384bdf1534fdbfda9e4
                validPosition =1;   
                counter ++;
            }
        }
    }
}



