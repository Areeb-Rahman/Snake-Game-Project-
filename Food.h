#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

using namespace std;

class Food
{
    private:
        GameMechs* gameMechRef;
        objPosArrayList* foodBucket;

    public:
            ~Food();
            Food(GameMechs * thisGMRef);

            void generateFoods(objPos blockOff);
            void getFoodPos(objPosArrayList &returnList) const;
        
        // More methods should be added here
};

#endif