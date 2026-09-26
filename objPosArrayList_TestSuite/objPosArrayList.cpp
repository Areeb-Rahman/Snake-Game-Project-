#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction,
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
    aList = new objPos[arrayCapacity];
}

// destructor
objPosArrayList::~objPosArrayList()
{
    delete[] aList; // we use [] because it is double pointer
}
// getter for size
int objPosArrayList::getSize() const
{
    return listSize;
}
// setter for head
void objPosArrayList::insertHead(objPos thisPos)
{
    // error handling
    if (listSize < arrayCapacity)
    {
        for (int i = listSize; i > 0; i--)
        {
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos;

        listSize++;
    }
}
// setter for tail
void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize < arrayCapacity)
    {
        aList[listSize] = thisPos;
        listSize += 1;
    }
}

// setter for head
void objPosArrayList::removeHead()
{
    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];
    }
    if (listSize > 0)
    {
        listSize--;
    }
}
// seter for tail
void objPosArrayList::removeTail()
{
    if (listSize > 0)
    {
        listSize -= 1;
    }
}

// getter for tail
objPos objPosArrayList::getHeadElement() const
{
    if (listSize > 0)
        return aList[0];
    return objPos(-1, -1, '\0'); // error object if empty
}

// getter for tail
objPos objPosArrayList::getTailElement() const
{
    if (listSize > 0)
        return aList[listSize - 1];
    return objPos(-1, -1, '\0');
}
// getter method
objPos objPosArrayList::getElement(int index) const
{ // assume highest index if greater than number of items in list
    if (index > listSize - 1)
    {
        index = listSize - 1;
    }
    // assume they want the first element if they have a negative index
    if (index < 0)
    {
        index = 0;
    }
    return aList[index];
}