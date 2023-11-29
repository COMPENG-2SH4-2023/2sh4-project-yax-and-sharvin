#include "objPosArrayList.h"

#include <iostream>
using namespace std;

objPosArrayList::objPosArrayList()
{
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;

    // Allocate memory on the heap
    aList = new objPos[sizeArray];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // std::cout << sizeList << std::endl;
    // std::cout << sizeArray << std::endl;

    if (sizeList < sizeArray)
    {
        // Shift existing elements to make room for the new element
        for (int i = sizeList; i > 0; --i)
        {
            aList[i] = aList[i - 1];
        }

        // Insert the new element at the head of the list
        aList[0] = thisPos;

        // Update the size of the list
        sizeList++;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{

    if (sizeList < sizeArray)
    {

        aList[sizeList] = thisPos;
        ++sizeList;
    }
}

void objPosArrayList::removeHead()
{

    if (sizeList > 0)
    {
        for (int i = 0; i < sizeList; ++i)
        {
            aList[i] = aList[i + 1];
        }
        --sizeList;
    }
}

void objPosArrayList::removeTail()
{

    if (sizeList > 0)
    {
        // degrements the size
        sizeList--;
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{

    if (sizeList > 0)
    {
        // Copy the objPos at the head of the list to returnPos
        returnPos = aList[0];
    }
}

void objPosArrayList::getTailElement(objPos &returnPos)
{

    if (sizeList > 0)
    {
        // returns the last element within the list
        returnPos = aList[sizeList - 1];
    }
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{

    if (sizeList > 0)
    {
        // return the specified index value
        returnPos = aList[index];
    }
}