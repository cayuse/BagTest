//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Implementation file for the class ArrayBag.
 @file ArrayBag.cpp */

#include "ArrayBag.h"
#include <cstddef>
#include <stdexcept>

template<class ItemType>
ArrayBag<ItemType>::ArrayBag(): itemCount(0), maxItems(DEFAULT_CAPACITY)
{
}  // end default constructor

template<class ItemType>
ArrayBag<ItemType>::~ArrayBag()
{
}  // end destructor

template<class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
    return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
    return itemCount == 0;
}  // end isEmpty

template<class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newEntry)
{
    bool hasRoomToAdd = (itemCount < maxItems);
    if (hasRoomToAdd)
    {
        items[itemCount] = newEntry;
        itemCount++;
    }  // end if

    return hasRoomToAdd;
}  // end add

/*
// STUB
 template<class ItemType>
 bool ArrayBag<ItemType>::remove(const ItemType& anEntry)
 {
    return false; // STUB
 }  // end remove
*/

template<class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anEntry)
{
    int locatedIndex = getIndexOf(anEntry);
    bool canRemoveItem = !isEmpty() && (locatedIndex > -1);
    if (canRemoveItem)
    {
        itemCount--;
        items[locatedIndex] = items[itemCount];
    }  // end if

    return canRemoveItem;
}  // end remove

template<class ItemType>
void ArrayBag<ItemType>::clear()
{
    itemCount = 0;
}  // end clear

template<class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
    int frequency = 0;
    int curIndex = 0;       // Current array index
    while (curIndex < itemCount)
    {
        if (items[curIndex] == anEntry)
        {
            frequency++;
        }  // end if

        curIndex++;          // Increment to next entry
    }  // end while

    return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anEntry) const
{
    return getIndexOf(anEntry) > -1;
}  // end contains

/* ALTERNATE 1: First version
template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& target) const 
{
   return getFrequencyOf(target) > 0;
}  // end contains
 
// ALTERNATE 2: Second version 
template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anEntry) const
{
   bool found = false;
   int curIndex = 0;        // Current array index
   while (!found && (curIndex < itemCount))
   {
      if (anEntry == items[curIndex])
      {
         found = true;
      } // end if
      
      curIndex++;           // Increment to next entry
   }  // end while   
   
   return found;
}  // end contains
*/

template<class ItemType>
vector<ItemType> ArrayBag<ItemType>::toVector() const
{
    vector<ItemType> bagContents;
    for (int i = 0; i < itemCount; i++)
        bagContents.push_back(items[i]);

    return bagContents;
}  // end toVector

// private
template<class ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType& target) const
{
    bool found = false;
    int result = -1;
    int searchIndex = 0;

    // If the bag is empty, itemCount is zero, so loop is skipped
    while (!found && (searchIndex < itemCount))
    {
        if (items[searchIndex] == target)
        {
            found = true;
            result = searchIndex;
        }
        else
        {
            searchIndex++;
        }  // end if
    }  // end while

    return result;
}  // end getIndexOf


// Homework part
    /* The result of thise operations will be a LinkedBag (since LinkedBag created it).
       However, since the argument to this method is of type BagInterface,
       it should be able to work with any ADT compliant object.
       Therefore, we'll handle the argument with ADT Primitives.
    */
    
template<class ItemType>
BagInterface<ItemType>* ArrayBag<ItemType>::Union(const BagInterface<ItemType> &otherBag) const throw(length_error)
{
    vector<ItemType> myVec = (*this).toVector();
    vector<ItemType> otherVec = otherBag.toVector();
    int lcv;
    if (myVec.size() + otherVec.size() > maxItems)
    {
        throw length_error("maxItems exceeded");
    }
    // don't create a new bag unless we are past the test.
    ArrayBag<ItemType>* newBag = new ArrayBag<ItemType>();

    for (lcv = 0; lcv < myVec.size(); lcv++)
    {
        newBag->add(myVec[lcv]);
    }
    for (lcv = 0; lcv < otherVec.size(); lcv++)
    {
        newBag->add(otherVec[lcv]);
    }

    return newBag;
}

template<class ItemType>
BagInterface<ItemType>* ArrayBag<ItemType>::intersection(const BagInterface<ItemType> &otherBag) const
{
    ArrayBag<ItemType>* newBag = new ArrayBag<ItemType>();
    ArrayBag<ItemType> myBagCopy = *this;
    vector<ItemType> otherBagVec = otherBag.toVector();
    ArrayBag<ItemType> otherBagCopy;
    for (int lcv = 0; lcv < otherBagVec.size(); lcv ++)
    {
        otherBagCopy.add(otherBagVec[lcv]);
    }


    vector<ItemType> myVec = (*this).toVector();
    for (int lcv = 0; lcv < myVec.size(); lcv ++)
        if (myBagCopy.contains(myVec[lcv]) && otherBagCopy.contains(myVec[lcv]))
        {
            newBag->add(myVec[lcv]);
            myBagCopy.remove(myVec[lcv]);
            otherBagCopy.remove(myVec[lcv]);
        }
    return newBag;
}

template<class ItemType>
BagInterface<ItemType>* ArrayBag<ItemType>::difference(const BagInterface<ItemType> &otherBag) const
{
    int lcv;
    vector<ItemType> myVec = (*this).toVector();
    vector<ItemType> otherVec = otherBag.toVector();
    ArrayBag<ItemType>* newBag = new ArrayBag<ItemType>();
    for ( lcv = 0; lcv < myVec.size(); lcv ++ )
    {
        newBag->add(myVec[lcv]);
    }
    for (lcv = 0; lcv < otherVec.size(); lcv ++ )
    {
        newBag->remove(otherVec[lcv]);
    }
    return newBag;
}

template<class ItemType>
BagInterface<ItemType>& ArrayBag<ItemType>::operator=(const BagInterface<ItemType> &rightHandSide)
{
   // Check for assignment to self
   if (this != &rightHandSide)
   {
      this->clear();  // Deallocate left-hand side
      int lcv;
      vector<ItemType> otherVec = rightHandSide.toVector();
      for (lcv = 0; lcv < otherVec.size(); lcv++)
      {
        this->add(otherVec[lcv]);
      }
   }  // end if
   
   return *this; 
}

template<class ItemType>
BagInterface<ItemType>* ArrayBag<ItemType>::operator+(const BagInterface<ItemType> &rightHandSide) const
{
    return(this->Union(rightHandSide) );
}

template<class ItemType>
BagInterface<ItemType>* ArrayBag<ItemType>::operator-(const BagInterface<ItemType> &rightHandSide) const
{
    return(this->difference(rightHandSide) );
}