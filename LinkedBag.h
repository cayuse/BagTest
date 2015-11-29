//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT bag: Link-based implementation.
    @file LinkedBag.h 
    Listing 4-3 */
#ifndef _LINKED_BAG
#define _LINKED_BAG

#include "BagInterface.h"
#include "Node.h"
#include <vector>

template<class ItemType>
class LinkedBag : public BagInterface<ItemType>
{
private:
    Node<ItemType>* headPtr; // Pointer to first node
    int itemCount;           // Current count of bag items

    // provate recursive node killer
    void chainDelete(Node<ItemType>* ptrToDelete);

    // Returns either a pointer to the node containing a given entry
    // or the null pointer if the entry is not in the bag.
    Node<ItemType>* getPointerTo(const ItemType& target) const;

public:
    LinkedBag();
    LinkedBag(const LinkedBag<ItemType>& aBag); // Copy constructor
    virtual ~LinkedBag();                       // Destructor should be virtual
    int getCurrentSize() const;
    bool isEmpty() const;
    bool add(const ItemType& newEntry);
    bool remove(const ItemType& anEntry);
    void clear();
    bool contains(const ItemType& anEntry) const;
    int getFrequencyOf(const ItemType& anEntry) const;

    vector<ItemType> toVector() const;

    /* ######################## Homework Here ##################### */

    /** @return new bag combined with contents of otherBag  */
    BagInterface<ItemType>* Union(const BagInterface<ItemType> &otherBag) const;
    /** @return new bag with intersection of otherBag */
    BagInterface<ItemType>* intersection(const BagInterface<ItemType> &otherBag) const;

    /** @return new bag with difference of otherBag */
    BagInterface<ItemType>* difference(const BagInterface<ItemType> &otherBag) const;

    /** Operator overloads (= + -) and have the usual meanings */
    BagInterface<ItemType>* operator=(const BagInterface<ItemType> &rightHandSide);

    BagInterface<ItemType>* operator+(const BagInterface<ItemType> &rightHandSide) const;

    BagInterface<ItemType>* operator-(const BagInterface<ItemType> &rightHandSide) const;
}
; // end LinkedBag

#endif
