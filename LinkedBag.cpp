//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT bag: Link-based implementation.
    @file LinkedBag.cpp */

#include "LinkedBag.h"
#include "Node.h"
#include <cstddef>
#include <vector>

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(NULL), itemCount(0)
{
}  // end default constructor

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag)
{
    itemCount = aBag.itemCount;
    Node<ItemType>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain

    if (origChainPtr == NULL)
        headPtr = NULL;  // Original bag is empty
    else
    {
        // Copy first node
        headPtr = new Node<ItemType>();
        headPtr->setItem(origChainPtr->getItem());

        // Copy remaining nodes
        Node<ItemType>* newChainPtr = headPtr;      // Points to last node in new chain
        origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer

        while (origChainPtr != NULL)
        {
            // Get next item from original chain
            ItemType nextItem = origChainPtr->getItem();

            // Create a new node containing the next item
            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr);

            // Advance pointer to new last node
            newChainPtr = newChainPtr->getNext();

            // Advance original-chain pointer
            origChainPtr = origChainPtr->getNext();
        }  // end while

        newChainPtr->setNext(NULL);              // Flag end of chain
    }  // end if
}  // end copy constructor

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
    clear();
}  // end destructor

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
    return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const
{
    return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{
    // Add to beginning of chain: new node references rest of chain;
    // (headPtr is null if chain is empty)
    Node<ItemType>* nextNodePtr = new Node<ItemType>();
    nextNodePtr->setItem(newEntry);
    nextNodePtr->setNext(headPtr);  // New node points to chain
    //   Node<ItemType>* nextNodePtr = new Node<ItemType>(newEntry, headPtr); // alternate code

    headPtr = nextNodePtr;          // New node is now first node
    itemCount++;

    return true;
}  // end add

template<class ItemType>
vector<ItemType> LinkedBag<ItemType>::toVector() const
{
    vector<ItemType> bagContents;
    Node<ItemType>* curPtr = headPtr;
    int counter = 0;
    while ((curPtr != NULL) && (counter < itemCount))
    {
        bagContents.push_back(curPtr->getItem());
        curPtr = curPtr->getNext();
        counter++;
    }  // end while
    return bagContents;
}  // end toVector

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry)
{
    Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
    bool canRemoveItem = !isEmpty() && (entryNodePtr != NULL
                                       );
    if (canRemoveItem)
    {
        // Copy data from first node to located node
        entryNodePtr->setItem(headPtr->getItem());

        // Delete first node
        Node<ItemType>* nodeToDeletePtr = headPtr;
        headPtr = headPtr->getNext();

        // Return node to the system
        nodeToDeletePtr->setNext(NULL);
        delete nodeToDeletePtr;
        nodeToDeletePtr = NULL;

        itemCount--;
    } // end if

    return canRemoveItem;
}  // end remove

template<class ItemType>
void LinkedBag<ItemType>::clear()
{
    // if the head ptr is NULL then there is nothing to do
    if (headPtr == NULL)
    {
        return;
    }
    // otherwise call into the recursive destroyer of objects
    chainDelete(headPtr);
    // clean up
    headPtr = NULL;
    itemCount = 0;
}

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
    int frequency = 0;
    int counter = 0;
    Node<ItemType>* curPtr = headPtr;
    while ((curPtr != NULL) && (counter < itemCount))
    {
        if (anEntry == curPtr->getItem())
        {
            frequency++;
        } // end if

        counter++;
        curPtr = curPtr->getNext();
    } // end while

    return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
    return (getPointerTo(anEntry) != NULL);
}  // end contains


// Homework part
/* The result of thise operations will be a LinkedBag (since LinkedBag created it).
   However, since the argument to this method is of type BagInterface,
   it should be able to work with any ADT compliant object.
   Therefore, we'll handle the argument with ADT Primitives.
*/
template<class ItemType>
BagInterface<ItemType>* LinkedBag<ItemType>::Union(const BagInterface<ItemType> &otherBag) const

{
    LinkedBag<ItemType>* newBag = new LinkedBag<ItemType>();
    *newBag = *this;
    int lcv;
    vector<ItemType> otherVec = otherBag.toVector();

    for (lcv = 0; lcv < otherVec.size(); lcv++)
    {
        newBag->add(otherVec[lcv]);
    }

    return newBag;
}

template<class ItemType>
BagInterface<ItemType>* LinkedBag<ItemType>::intersection(const BagInterface<ItemType> &otherBag) const
{
    LinkedBag<ItemType>* newBag = new LinkedBag<ItemType>();
    int lcv;
    LinkedBag<ItemType> myBagCopy = *this;
    vector<ItemType> otherBagVec = otherBag.toVector();
    LinkedBag<ItemType> otherBagCopy;
    for (int lcv = 0; lcv < otherBagVec.size(); lcv ++)
    {
        otherBagCopy.add(otherBagVec[lcv]);
    }
    vector<ItemType> myVec = (*this).toVector();
    for (lcv = 0; lcv < myVec.size(); lcv ++)
        if (myBagCopy.contains(myVec[lcv]) && otherBagCopy.contains(myVec[lcv]))
        {
            newBag->add(myVec[lcv]);
            myBagCopy.remove(myVec[lcv]);
            otherBagCopy.remove(myVec[lcv]);
        }
    return newBag;
}

template<class ItemType>
BagInterface<ItemType>* LinkedBag<ItemType>::difference(const BagInterface<ItemType> &otherBag) const

{
    int lcv;
    vector<ItemType> myVec = (*this).toVector();
    vector<ItemType> otherVec = otherBag.toVector();
    LinkedBag<ItemType>* newBag = new LinkedBag<ItemType>();
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
BagInterface<ItemType>* LinkedBag<ItemType>::operator=(const BagInterface<ItemType> &rightHandSide)
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
   
   return this; 
}
template<class ItemType>
BagInterface<ItemType>* LinkedBag<ItemType>::operator+(const BagInterface<ItemType> &rightHandSide) const
{
    return(this->Union(rightHandSide) );
}

template<class ItemType>
BagInterface<ItemType>* LinkedBag<ItemType>::operator-(const BagInterface<ItemType> &rightHandSide) const
{
    return(this->difference(rightHandSide) );
}

// private
// Returns either a pointer to the node containing a given entry
// or the null pointer if the entry is not in the bag.
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const
{
    bool found = false;
    Node<ItemType>* curPtr = headPtr;

    while (!found && (curPtr != NULL))
    {
        if (anEntry == curPtr->getItem())
            found = true;
        else
            curPtr = curPtr->getNext();
    } // end while

    return curPtr;
} // end getPointerTo

template<class ItemType>
void LinkedBag<ItemType>::chainDelete(Node<ItemType>* ptrToDelete)
{
    Node<ItemType>* nextPtr;
    // get the next pointer if there is one
    nextPtr = ptrToDelete->getNext();

    // if there is, recursively call into this function with it
    if (nextPtr) //NULL should result in a false
    {
        chainDelete(nextPtr);
    }

    // Return node to the system
    ptrToDelete->setNext(NULL);
    delete ptrToDelete;
    ptrToDelete = NULL;
}

