//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Header file for an array-based implementation of the ADT bag.
 @file ArrayBag.h */

#ifndef _ARRAY_BAG
#define _ARRAY_BAG

#include "BagInterface.h"
#include <stdexcept>

template<class ItemType>
class ArrayBag : public BagInterface<ItemType>
{
private:
    static const int DEFAULT_CAPACITY = 6; // Small size to test for a full bag
    ItemType items[DEFAULT_CAPACITY];      // Array of bag items
    int itemCount;                         // Current count of bag items
    int maxItems;                          // Max capacity of the bag

    // Returns either the index of the element in the array items that
    // contains the given target or -1, if the array does not contain
    // the target.
    int getIndexOf(const ItemType& target) const;

public:
    ArrayBag();
    virtual ~ArrayBag();
    int getCurrentSize() const;
    bool isEmpty() const;
    bool add(const ItemType& newEntry);
    bool remove(const ItemType& anEntry);
    void clear();
    bool contains(const ItemType& anEntry) const;
    int getFrequencyOf(const ItemType& anEntry) const;
    vector<ItemType> toVector() const;

    /* ######################## Homework Here ##################### */
    /** @return a new ArrayBag combined with contents of otherBag */
    BagInterface<ItemType>* Union(const BagInterface<ItemType> &otherBag) const throw(out_of_range);

    /** @return new ArrayBag with intersection of otherBag */
    BagInterface<ItemType>* intersection(const BagInterface<ItemType> &otherBag) const;

    /** @return a new ArrayBag with difference of otherBag */
    BagInterface<ItemType>* difference(const BagInterface<ItemType> &otherBag) const;

    /** Operator overloads (= + -) and have the usual meanings */
    BagInterface<ItemType>& operator=(const BagInterface<ItemType> &rightHandSide);
    
    BagInterface<ItemType>* operator+(const BagInterface<ItemType> &rightHandSide) const;
    
    BagInterface<ItemType>* operator-(const BagInterface<ItemType> &rightHandSide) const;

}
; // end ArrayBag
    #include "ArrayBag.cpp"

#endif
